#include "LOF.h"
#include <math.h>

float distance(data_t *a,data_t *b)
{
    return sqrt(pow((a->traffic_norm - b->traffic_norm),2)+pow((a->n_flow_norm - b->n_flow_norm),2) );
}

void swap(n_b *a, n_b *b)
{
    n_b t;
    t = *a;
    *a = *b;
    *b = t; 
}

void bubble_sort(data_t *a,int n)
{
    for (int i=0;i<K;i++)
    {
        for (int j=i+1;j<n;j++)
        {
            if (a->neighbor[i].distance > a->neighbor[j].distance)
            {
                swap (&a->neighbor[i],&a->neighbor[j]);
            }
        }
    }
}

float k_dis(data_t *a)
{
    return a->neighbor[K-1].distance;
}

float max(float a, float b)
{
    if (a >=b)
        return a;
    return b;
}

float reach_dis(data_t *a, data_t *b)
{
    return max(k_dis(b),distance(a,b));
}

void lrd_k(data_t *Arr[],int n)
{
    for (int i=0;i<DATANUM;i++)
        Arr[i]->index = i;
    for (int i=0;i<n;i++)
    {
        int k=0;
        for (int j=0;j<n;j++)
        {
            if (i != j )
            {
                Arr[i]->neighbor[k].index_list = j;
                Arr[i]->neighbor[k].distance = distance(Arr[i],Arr[j]);
		        k++;
            }
        }
    }
    for (int i=0;i<n;i++)
    {
        bubble_sort(Arr[i],DATANUM);
    }
    for (int i=0;i<n;i++)
    {
        Arr[i]->lrd = 0;
        for (int j=0;j<K;j++)
        {   
            Arr[i]->lrd += reach_dis(Arr[i],Arr[Arr[i]->neighbor[j].index_list]);
        }
        Arr[i]->lrd = K/Arr[i]->lrd;
    }
    
}

void LOF_training(data_t *Arr[],int n)
{
    lrd_k(Arr,n);
    for (int i=0;i<n;i++)
    {
        Arr[i]->lof =0;
        for (int j=0;j<K;j++)
        {
            Arr[i]->lof += Arr[Arr[i]->neighbor[j].index_list]->lrd;
        }
        Arr[i]->lof = Arr[i]->lof/(K*Arr[i]->lrd);
    }
}

float LOF(data_t *a,data_t *Arr[],int n)
{
        for (int j=0;j<n;j++)
        {
                a->neighbor[j].index_list = j;
                a->neighbor[j].distance = distance(a,Arr[j]);
        }
        bubble_sort(a,DATANUM);
        a->lrd = 0;
        for (int j=0;j<K;j++)
        {   
            a->lrd += reach_dis(a,Arr[a->neighbor[j].index_list]);
        }
        a->lrd = K/a->lrd;

    float lof = 0;
    for (int i=0;i<K;i++)
    {
        lof += Arr[a->neighbor[i].index_list]->lrd;
    }
    lof = lof/(K*a->lrd);
    return lof;
}

float calc_mu(float *arr,int n)
{
    float sum=0;
    for (int i=0;i<n;i++)
    {
        sum += arr[i];
    }
    return sum/n;
}

float calc_sigma(float *arr,int n)
{
    float s=0;
    float mu = calc_mu(arr,n);
    for (int i=0;i<n;i++)
    {
        s += pow ((arr[i] -mu),2);
    }
    return sqrt(s/n);
}

float normalize(float x, float mu,float sigma)
{
    return (tanh(0.1*(x-mu)/sigma)+1)/2;
}

