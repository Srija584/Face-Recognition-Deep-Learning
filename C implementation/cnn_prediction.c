#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
int row=80;
int column=80;
int ITER;
int ITER_SUB;

float *miniCNN(float patch[3][3],int p,float w1[3][4],float w2[4],float w3[3],float bias1);
float max(float p[]);
float predict(float patch[3][3],float demo_wt[20]);

void CNN(float input[row][column],int row,int column)
{
	int i,j,c,d,k,l,index1,index2,count=-1,mn,p_1,p_2,iter,it1,it2,it3,iterations[row*column];
	float w1[3][4],demo_wt[20],predicted_output[row][column],w11[3][4],w21[4],bias11,
	maxi,patch[3][3],input_new[row+2][column+2],w3[3],w2[4],bias1,p;
	srand((unsigned)time(NULL));
	FILE *fp,*fp1;

	char buffer[100];
	sprintf(buffer,"/home/srija/tensorflow/pie_output/models/weights_p%d_45_0.txt",ITER );
	fp=fopen(buffer,"r");

	char buffer1[100];
	sprintf(buffer1,"/home/srija/tensorflow/pie_output/results/45/predicted_p%d_p%d.txt",ITER, ITER_SUB );
	fp1=fopen(buffer1,"w");

	maxi=input[0][0];
	for(i=0;i<row;i++)
	for(j=0;j<column;j++)
	{
		if(input[i][j]>maxi)
			maxi=input[i][j];
	}

	for(i=0;i<row;i++)
	for(j=0;j<column;j++)
	{
		input[i][j]=(input[i][j]/maxi);
	}

	printf("\n\n\n");

	//float w2[4]={0.5,0.8,0.9,0.6};
//	float bias1=0.2,bias2=1,eta=0.1;
	float error[100],*F;
	float FinalWeight[row*column][20];
	float padded_matrix[row+1][column+1],w31[3];
	printf("hi\n");
	
	//printf("CNN\n");

	for(i=0;i<row+2;i++)
	{
		for(j=0;j<column+2;j++)
			input_new[i][j]=0;
	}


	for(i=1;i<=row;i++)
	{
		for(j=1;j<=column;j++)
			input_new[i][j]=input[i-1][j-1];
	}

	for(j=0;j<=column+1;j++)
		input_new[0][j]=0;

	for(j=0;j<=column+1;j++)
		input_new[row+1][j]=0;		

	for(i=0;i<=row+1;i++)
		input_new[i][0]=0;

	for(i=0;i<=row+1;i++)
		input_new[i][column+1]=0;

	// for(i=0;i<=row+1;i++)
	// {
	// 	for(j=0;j<=column+1;j++)
	// 		printf("%f ",input_new[i][j]);
	// 	printf("\n");
	// }
	
	float initial_weights[20];
	int we;
	
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
		{
			//count++;
			k=i;
			l=j;
			c=0;
			d=0;
			index1=i;
			index2=j;
			for(c=0;c<3;c++)
			{
				for(d=0;d<3;d++)
					{
						// printf("c,d: %d %d\n",c,d);
						// printf("%f\n", input_new[k+c][l+d]);
						patch[c][d]=input_new[k+c][l+d];
						
					}
			}
			
			for(we=0;we<20;we++)
			{
				fscanf(fp,"%f",&initial_weights[we]);
				// printf("%f\n",initial_weights[we]);
			}
			int count_w=-1,c1,c2;
			for(c1=0;c1<3;c1++)
			{
				for(c2=0;c2<4;c2++)
				{
					count_w++;
					w1[c1][c2]=initial_weights[count_w];
				}
			
			}
			
			for(c1=0;c1<4;c1++)
			{
				count_w++;
				w2[c1]=initial_weights[count_w];
			}
			
			for(c1=0;c1<3;c1++)
			{
				count_w++;
				w3[c1]=initial_weights[count_w];
			}
		
			bias1=initial_weights[19];
			
			for(c1=0;c1<20;c1++)
			demo_wt[c1]=initial_weights[c1];
			//F=miniCNN(patch,output[index1][index2],w1,w2,w3,bias1);
			p=predict(patch,demo_wt);
			predicted_output[i][j]=p;
			// printf("predicted=%f\n",p);
		}
	}
	//free(F);
	count=-1;
	printf("Printing Final\n");
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++){
			count++;
		// printf("%f %d\n ",predicted_output[i][j],count);
	}
		// printf("\n");
	}
	
	//return(FinalWeight);
	for(i=0;i<row;i++)
	{
			for(j=0;j<column;j++)
			{
				/*if(predicted_output[i][j]>0.50)
				fprintf(fp1,"1 ");
				else
				fprintf(fp1,"0 ");
*/
			fprintf(fp1,"%f ",predicted_output[i][j]*maxi);
			}
				
	}
	fclose(fp);
	fclose(fp1);
		
}
float *miniCNN(float patch[3][3],int p,float w1[3][4],float w2[4],float w3[3],float bias1)
{
	//printf("\n\nminiCNN\n\n");

	int row=3,column=3,count=-1,k,l,c,d,q,r,i,j,count2,count3;
	float sum[4][3],sum_p[4][3],demo[2][2],node[3]={0,0,0},sums1=0,sums2=0,sums3=0,maximum[3],demo2[4],e,del_layer2[3],del_layer1[3][4],del_w2[4],del_w1[3][4];
	float eta=0.25,layer1[3][4],sums[3][4],del_pool[3][4],weight_layer1[3][4],window[4][2][2],del_w3[4];
 	float *weights=(float *)malloc(20*sizeof(float));
	float w11[3][4],w21[4],w31[3],bias11;
	/*for(i=0;i<3;i++)
	for(j=0;j<3;j++)
	printf("%d ",patch[i][j]);
*/
	for(i=0;i<3;i++)
	for(j=0;j<4;j++)
	w11[i][j]=w1[i][j];
	
	for(i=0;i<4;i++)
	w21[i]=w2[i];

	for(i=0;i<3;i++)
	w31[i]=w3[i];	

	bias11=bias1;

//	printf("demoloop\n"); 
	for(i=0;i<2;i++)
		{
			for(j=0;j<2;j++)
			{
				count++;
				k=i;
				l=j;
				c=0;
				d=0;
				count2=-1;
				count3=-1;
				for(c=0;c<2;c++)
				{
					for(d=0;d<2;d++)
					{
						count2++;
						demo[c][d]=patch[c+k][d+l];
						window[count][c][d]=patch[c+k][d+l];
				//		printf("%f ",demo[c][d]);
	//					
			//	printf("\n");				
				
					}
				}
		//	printf("demo end\n");
				sums1=0;
				sums2=0;
				sums3=0;
				
				for(q=0;q<2;q++)
					{
						for(r=0;r<2;r++)
							{
								count3++;
//								printf("%d ",count3);
//								printf("%f ",w1[0][count3]);
//								printf("%f ",demo[q][r]);
								sums1+=(demo[q][r]*w11[0][count3]);
								sums[0][count]=demo[q][r]*w11[0][count3];
//								printf("%f ",sums[0][count]);

//								printf("%f ",w1[1][count3]);
								sums2+=(demo[q][r]*w11[1][count3]);
								sums[1][count]=demo[q][r]*w11[1][count3];
//								printf("%f ",sums[1][count]);

//								printf("%f ",w1[2][count3]);
								sums3+=(demo[q][r]*w11[2][count3]);
								sums[2][count]=demo[q][r]*w11[2][count3];
//								printf("%f\n",sums[2][count]);
							}
					}
//					printf("\n");	
				sum_p[count][0]=sums1;
				sum_p[count][1]=sums2;
				sum_p[count][2]=sums3;

				sum[count][0]=1/(1+(1/exp(sums1)));
				sum[count][1]=1/(1+(1/exp(sums2)));
				sum[count][2]=1/(1+(1/exp(sums3)));
			//	printf("Hii\n");
			}
							
		}

		float sum_hidden2[3];
	/*for(i=0;i<3;i++){
	for(j=0;j<4;j++){
	printf("%f ",sum[j][i]);}
	printf("\n");}
	printf("\n");
*/
		sums1=0;


		for(i=0;i<3;i++)
		{
			sums1=0;
			for(j=0;j<4;j++)
			sums1+=sum[j][i]*w21[j];
			sum_hidden2[i]=1/(1+(1/exp(sums1)));
		}
		
		sums1=0;
		for(i=0;i<3;i++)
		sums1+=sum_hidden2[i]*w31[i];

		float sig,grad;
		sig=1/(1+(1/exp(sums1)))+bias1; //predicted output
		//printf("%f\n",sig);
		e=p-sig;

		//back propagation 
		grad=sig*(1-sig)*(sig-p); //final output gradient

		bias11=bias11-eta*grad;

		for(i=0;i<3;i++)
		{
			del_w3[i]=-eta*grad*sum_hidden2[i];
			w31[i]+=del_w3[i];
		}

		for(i=0;i<3;i++)
		del_layer2[i]=sum_hidden2[i]*(1-sum_hidden2[i])*(w31[i]*grad);

		for(i=0;i<4;i++)
		{
			sums1=0;
			for(j=0;j<3;j++)
			{
				sums1+=sum[i][j]*del_layer2[j];
			}
			del_w2[i]=-eta*sums1;
			w21[i]+=del_w2[i];
		}

		for(i=0;i<3;i++)
		{
			for(j=0;j<4;j++)
			{
				del_layer1[i][j]=sum[j][i]*(1-sum[j][i])*((del_layer2[i]*w21[0])+(del_layer2[i]*w21[1])+(del_layer2[i]*w21[2])+(del_layer2[i]*w21[3]));
			}
		}
		
		float t[3][4];
	for(i=0;i<3;i++)
	for(j=0;j<4;j++)
	t[i][j]=0;

	count2=-1;
	for(i=0;i<4;i++)
	{
	count2=-1;
		for(j=0;j<2;j++)
		{
			for(k=0;k<2;k++)
			{
				count2++;
				t[0][count2]+=window[i][j][k]*del_layer1[0][i];
				t[1][count2]+=window[i][j][k]*del_layer1[1][i];
				t[2][count2]+=window[i][j][k]*del_layer1[2][i];
			}
		}
	}

	/*for(i=0;i<3;i++)
	for(j=0;j<4;j++)
	printf("%f ",t[i][j]);
	*/	
	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
			w11[i][j]=w11[i][j]-eta*t[i][j];
	//		printf("%f ",w1[i][j]);
	}
	/*printf("\n");
	for(i=0;i<4;i++)
	printf("%f ",w2[i]);
	printf("\n");
	for(i=0;i<3;i++)
	printf("%f ",w3[i]);
	printf("back propagation ends\n");*/
	count=-1;
	count=-1;
	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
			{
				count++;
//				printf("%d ",count);
				weights[count]=w11[i][j];
	//			printf("%f ",weights[count]);
			}
	//	printf("\n");
	}	

	for(i=0;i<4;i++)
		{
			count++;
			weights[count]=w21[i];
		}

	for(i=0;i<3;i++)
		{
			count++;
			weights[count]=w31[i];
		}

	weights[19]=bias11;
	//printf("return to CNN \n");
	return(weights);
}

float max(float p[])
{
//	printf("float\n");
	float m;
	int i;
//	for(i=0;i<4;i++)
//	printf("%f ",p[i]);
	m=p[0];
	for(i=0;i<4;i++)
		if(p[i]>m)
			m=p[i];
//	printf("%f------",m);
	return m;
}

int main(int argc, char *argv[])
{
	if (argc != 3) 
        {
        	printf("Wrong parameters. Usage: ./cnn_prediction [iteration number]\n");
		return 1;
	}
        sscanf(argv[1], "%d", &ITER);
		printf("ITER : %d\n", ITER);
		sscanf(argv[2], "%d", &ITER_SUB);
        printf("ITER_SUB : %d\n", ITER_SUB);
	float input[row][column],t;
	time_t tm;
	srand((unsigned) time(&tm));
	printf("from prediction\n");
	int output[row][column],i,j,d,f;

	char buffer[100];
	sprintf(buffer,"/media/srija/Seagate Backup Plus Drive/images/pie_jpg/experiments/exp/p%d_im45.txt",ITER );

	FILE *f1,*f2;
	f1=fopen(buffer,"r");
	
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
		{
			fscanf(f1,"%d",&f);
			input[i][j]=f;
		}
	}

	

	fclose(f1);
	//fclose(f2);

	CNN(input,row,column);
	return 0;
	
}
		
float predict(float patch[3][3],float demo_wt[20])
{
	int row=3,column=3,count=-1,k,l,c,d,q,r,i,j,count2,count3;
	float sum[4][3],demo[2][2],node[3]={0,0,0},sums1=0,sums2=0,sums3=0,maximum[3],demo2[4],e,del_layer2[3],del_layer1[3][4],del_w2[3],del_w1[3][4];
	float eta=0.005,layer1[3][4],sums[3][4],w1[3][4],w2[4],w3[3],bias1;
	float weights[20];

	for(i=0;i<3;i++)
	for(j=0;j<4;j++){
		count++;
		w1[i][j]=demo_wt[count];
	}
	for(i=0;i<4;i++)
	{
		count++;
		w2[i]=demo_wt[count];
	}

	for(i=0;i<4-1;i++)
	{
		count++;
		w3[i]=demo_wt[count];
	}
	bias1=demo_wt[19];
	count=-1;
	for(i=0;i<2;i++)
		{
			for(j=0;j<2;j++)
			{
				count++;
				k=i;
				l=j;
				c=0;
				d=0;
				count2=-1;
				count3=-1;
				for(c=0;c<2;c++)
				{
					for(d=0;d<2;d++){
						count2++;
						demo[c][d]=patch[c+k][d+l];
			//			printf("%f ",demo[c][d]);
						
			//	printf("\n");				
			//	printf("");
				
				}
				}
				sums1=0;
				sums2=0;
				sums3=0;
				for(q=0;q<2;q++)
					{
						for(r=0;r<2;r++)
							{
								count3++;
//								printf("%d ",count3);
//								printf("%f ",w1[0][count3]);
//								printf("%f ",demo[q][r]);
								sums1+=(demo[q][r]*w1[0][count3]);
								sums[0][count]=demo[q][r]*w1[0][count3];
//								printf("%f ",sums[0][count]);

//								printf("%f ",w1[1][count3]);
								sums2+=(demo[q][r]*w1[1][count3]);
								sums[1][count]=demo[q][r]*w1[1][count3];
//								printf("%f ",sums[1][count]);

//								printf("%f ",w1[2][count3]);
								sums3+=(demo[q][r]*w1[2][count3]);
								sums[2][count]=demo[q][r]*w1[2][count3];
//								printf("%f\n",sums[2][count]);
							}
					}
			//		printf("\n");	
				sum[count][0]=sums1;
				sum[count][1]=sums2;
				sum[count][2]=sums3;
			}	
		
		//printf("----------\n");			
		}
		float sum_hidden2[3];

		sums1=0;

		for(i=0;i<3;i++)
		{
			sums1=0;
			for(j=0;j<4;j++)
			sums1+=sum[j][i]*w2[j];
			sum_hidden2[i]=1/(1+(1/exp(sums1)));
		}
		
		sums1=0;
		for(i=0;i<3;i++)
		sums1+=sum_hidden2[i]*w3[i];

		float sig,grad;
		sig=1/(1+(1/exp(sums1)))+bias1; //predicted output
		return(sums1);
		printf("hello\n");
}

