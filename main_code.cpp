#include<iostream>
#include<fstream>
#include<conio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
#include<stdio.h>

using namespace std;

int i,j=0,n=50000,TP=0,TN=0;
float resolution[1000],pixels[1000],zoom[1000],focus[1000],weight[1000],price[1000],affordability[1000];
float yes=0,no=0;
float rnM[200],psM[200],zmM[200],fsM[200],wtM[200],peM[200],ayM[200];
double rn,ps,zm,fs,wt,pe,ay;


void find_yes_no()
{
    float temp;
    for(i=0; i<368; i++)
    {
        if(affordability[i]==1)
            yes++;
        else
            no++;
    }
    temp=yes;
    yes=(float)yes/(yes+no);
    no=(float)no/(temp+no);;
}

double find_meu(float temporary_array[1000],int class_type)
{
    double meu,sum=0;
    int c=0;

    for(i=0; i<368; i++)
    {
        if(affordability[i]==class_type)
        {
            sum+=temporary_array[i];
            c++;
        }
    }
   // cout<<"sum="<<sum<<" c="<<c<<" ";
    meu=(double)(sum)/c;
    //cout<<meu<<" \n";

    return meu;
}

double find_sigma(float temporary_array[1000],double mean,int class_type)
{
    double sigma,temp,sum=0;
    int c=0;

    for(i=0; i<368; i++)
    {
        if(affordability[i]==class_type)
        {
            temp=temporary_array[i]-mean;
            sum+=pow(temp,2);
            c++;
        }
    }
    //cout<<"sum="<<sum<<" c="<<c<<" ";
    sigma=(double)(sum)/c;
    return pow(sigma,0.5);
}

double expression(double x,double mean,double variance)
{
    return exp(-0.5*pow(((x-mean)/variance),2));
}

double find_VALUE(double low,double dx,double mean,double variance)
{
    double sum=0;
    for(int i=0; i<=n; i++)
    {
        double xi=low+i*dx;
        double fun=expression(xi,mean,variance);
        double rect=fun*dx;
        sum+=rect;
    }
   // cout<<"sum="<<sum<<" ";
    return sum;
}

double resolution_calculation(int class_type)
{
    double low=rn-0.001;
    double up=rn+0.001;
    double mean=find_meu(resolution,class_type);
    double variance=find_sigma(resolution,mean,class_type);
    //cout<<" variance="<<variance;
    double dx=(double)(up-low)/n;
    double result=find_VALUE(low,dx,mean,variance);
    double final_result=pow((2.506628275*variance),-1)*result;
   // cout<<"resolution->final result="<<final_result<<" \n\n";
    return final_result;
}

double pixels_calculation(int class_type)
{
    double low=ps-0.001;
    double up=ps+0.001;
    double mean=find_meu(pixels,class_type);
    double variance=find_sigma(pixels,mean,class_type);
   // cout<<" variance="<<variance;
    double dx=(double)(up-low)/n;
    double result=find_VALUE(low,dx,mean,variance);
    double final_result=pow((2.506628275*variance),-1)*result;
    //cout<<"pixels->final result="<<final_result<<" \n\n";
    return final_result;

}

double zoom_calculation(int class_type)
{
    double low=zm-0.001;
    double up=zm+0.001;
    double mean=find_meu(zoom,class_type);
    double variance=find_sigma(zoom,mean,class_type);
   // cout<<" variance="<<variance;
    double dx=(double)(up-low)/n;
    double result=find_VALUE(low,dx,mean,variance);
    double final_result=pow((2.506628275*variance),-1)*result;

   // cout<<"zoom->final result="<<final_result<<" \n\n";
    return final_result;


}

double focus_calculation(int class_type)
{
    double low=fs-0.001;
    double up=fs+0.001;
    double mean=find_meu(focus,class_type);
    double variance=find_sigma(focus,mean,class_type);
   // cout<<" variance="<<variance;
    double dx=(double)(up-low)/n;
    double result=find_VALUE(low,dx,mean,variance);
    double final_result=pow((2.506628275*variance),-1)*result;

   // cout<<"focus->final result="<<final_result<<" \n\n";
    return final_result;


}

double weight_calculation(int class_type)
{
    double low=wt-0.001;
    double up=wt+0.001;
    double mean=find_meu(weight,class_type);
    double variance=find_sigma(weight,mean,class_type);
    //cout<<" variance="<<variance;
    double dx=(double)(up-low)/n;
    double result=find_VALUE(low,dx,mean,variance);
    double final_result=pow((2.506628275*variance),-1)*result;

    //cout<<"weight->final result="<<final_result<<" \n\n";
    return final_result;


}

double price_calculation(int class_type)
{
    double low=pe-0.001;
    double up=pe+0.001;
    double mean=find_meu(price,class_type);
    double variance=find_sigma(price,mean,class_type);
    //cout<<" variance="<<variance;
    double dx=(double)(up-low)/n;
    double result=find_VALUE(low,dx,mean,variance);
    double final_result=pow((2.506628275*variance),-1)*result;

   // cout<<"pixel->final result="<<final_result<<" \n\n";
    return final_result;
}

int main()
{
    double result_0,result_1;

    ifstream file;
    file.open("training.txt");

    ifstream test;
    test.open("test.txt");

    ofstream f;
    f.open("training_output.txt");

    for(i=0; i<368; i++)
        file>>resolution[i]>>pixels[i]>>zoom[i]>>focus[i]>>weight[i]>>price[i]>>affordability[i];

    find_yes_no();
    //char press='1';
    int p=0;
    while(p!=10)
    {



    while(j!=124)
    {
       // input_value();
        j=rand()%123;
        file>>rnM[j]>>psM[j]>>zmM[j]>>fsM[j]>>wtM[j]>>peM[j]>>ayM[j];

        rn=rnM[j];
        ps=psM[j];
        zm=zmM[j];
        fs=fsM[j];
        wt=wtM[j];
        pe=peM[j];
        ay=ayM[j];

        result_1=resolution_calculation(1)*pixels_calculation(1)*zoom_calculation(1)*focus_calculation(1)*weight_calculation(1)*price_calculation(1);
        result_0=resolution_calculation(0)*pixels_calculation(0)*zoom_calculation(0)*focus_calculation(0)*weight_calculation(0)*price_calculation(0);

      //  cout<<result_1<<" "<<result_0;

       // f<<"Resolution:"<<rn<<" Pixels:"<<ps<<" Zoom:"<<zm<<" Focus:"<<fs<<" Weight:"<<wt<<" Price:"<<pe<<"\n";
        if(result_1>result_0)
        {
            //f<<"Affordability Yes(1)\n\n ";
           cout<<j<<"->yes\n";
            if(ay==1)
                TP++;
        }
        else
        {
            //f<<"Affordability No(0)\n\n ";
           cout<<j<<"->No\n";
              if(ay==0)
                TN++;
        }


       /* cout<<"\nPress 0 Stop! \nOther continue.\n";
        cin>>press;*/
        j++;




    }
        cout<<TP+TN;
        f<<"Accuracy:"<<((float)(TP+TN)/123)*100<<"%";
        file.close();
       p++;
        j=0;
    /*cout<<TP+TN;
    f<<"Accuracy:"<<((float)(TP+TN)/123)*100<<"%";

    //cout<<"ass";*/

    }
}
