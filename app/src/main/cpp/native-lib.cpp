#include <jni.h>
#include <string>

int index(int * a, int b){
    int k;
    for(k=0;k<9;k++){
        if(a[k]==b){
            return k;
        }
    }
    return -1;
}

int compare(int * a, int *b){
    int k;
    for(k=0;k<9;k++){
        if(a[k]!=b[k]){
            return 0;
        }
    }
    return 1;
}

extern "C" JNIEXPORT jstring JNICALL
Java_com_vaca_klotski_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    int a[9]={0,1,2,3,4,5,6,7,8};
    int temp[9]={0,0,0,0,0,0,0,0,0};
    int temp2[9]={0,0,0,0,0,0,0,0,0};
    srand(time(NULL));
    int *x=(int *)malloc(90000000*4);
    int *y=(int *)malloc(90000000*4);
    int *z=(int *)malloc(9000*4);

    int c[9][4]={{1,3,-1,-1},{2,4,0,-1},{5,1,-1,-1},{4,6,0,-1},{5,7,3,1},{8,4,2,-1},{7,3,-1,-1},{8,6,4,-1},{7,5,-1,-1}};
    int c2[9][4]={{4,2,-1,-1},{4,2,3,-1},{2,3,-1,-1},{4,2,1,-1},{4,2,3,1},{2,3,1,-1},{4,1,-1,-1},{4,3,1,-1},{3,1,-1,-1}};

    int d[9]={2,3,2,3,4,3,2,3,2};
    int origin[]={0,1,2,3,4,5,7,6,8};
    int ga=index(a,8);
    int j;
    int i;
    int b;
    memcpy(x,a,36);
    int n=0,m=0;
    int ff;
    int s;
    int yes=0;
    y[0]=ga;
    y[2]=0;
    y[1]=0;
    int k;
    while(1){
        ff=y[n];
        for(j=0;j<d[ff];j++){
            memcpy(temp,x+n,36);
            temp[ff]=temp[c[ff][j]];
            temp[c[ff][j]]=8;


            s=0;
            for(k=0;k<m+1;k+=9){
                if(compare(x+k,temp)){
                    s=1;
                    break;
                }
            }
            if(s==0){
                m=m+9;
                memcpy(x+m,temp,36);
                y[m]=c[ff][j];
                y[m+1]=n+1;
                y[m+2]=c2[ff][j];
                if(compare(temp,origin)){
                    yes=1;
                    goto End;
                }
            }
        }

        n+=9;
        if(n>m)break;
    }
    End:
    if(yes){
        s=0;
        int v=m+1;
        while(1){
            z[s]=y[v+1];
            v=y[v];
            s++;
            if(v==0)break;
        }
        printf("count:%d\n",s-1);
        for(k=s-2;k>=0;k--)printf("%d   ",z[k]);
    }else{
        printf("gaga:%d\n",m);
        s=0;
        int ss=0;
        int v,v2;
        for(v=10;v<=m+1;v+=9){
            v2=v;
            s=0;
            while(1){
                v2=y[v2];
                s++;
                if(v2==0)break;

            }
            s--;
            if(s>ss)ss=s;
        }


        printf("none:%d\n",ss);
    }

    free(x);
    free(y);
    return env->NewStringUTF(hello.c_str());
}