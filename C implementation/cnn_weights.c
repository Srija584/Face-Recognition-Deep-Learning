#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
#include<string.h>
int row=80;
int column=80;
int ITER;

float *miniCNN(float patch[3][3],int p,float w1[3][4],float w2[4],float w3[3],float bias1);
float max(float p[]);
float predict(float patch[3][3],float demo_wt[20]);

void CNN(float input[row][column],float output[row][column],int row,int column, int ITER)

{
	int i,j,c,d,k,l,index1,index2,count=-1,mn,p_1,p_2,iter,it1,it2,it3,iterations[row*column];
	float w1[3][4],demo_wt[20],predicted_output[row][column],w11[3][4],w21[4],bias11,maxi,patch[3][3],input_new[row+2][column+2],w3[3];
	srand((unsigned)time(NULL));
	FILE *fp, *f1;

	char buffer[100];
	sprintf(buffer,"/home/srija/tensorflow/pie_output/models/weights_p%d_45_0.txt",ITER );

	
	f1=fopen("/media/srija/Seagate Backup Plus Drive/images/pie_jpg/experiments/temp_45.txt","r");
	fp=fopen(buffer,"w");
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

    maxi=output[0][0];
	for(i=0;i<row;i++)
	for(j=0;j<column;j++)
	{
		if(output[i][j]>maxi)
			maxi=output[i][j];
	}

	for(i=0;i<row;i++)
	for(j=0;j<column;j++)
	{
		output[i][j]=(output[i][j]/maxi);
	}

/*	for(i=0;i<10;i++){
	for(j=0;j<10;j++)
	{
		printf("%f ",input[i][j]);
	}
	printf("\n");
	}*/

	printf("\nweights\n");
	for(i=0;i<3;i++)
	{
		for(j=0;j<4;j++)
		{
			w1[i][j]=rand()/(float)(RAND_MAX/1);
			printf("%f ",w1[i][j]);
		}
	//printf("\n");
	}

	for(i=0;i<3;i++)
	{
			w3[i]=rand()/(float)(RAND_MAX/1);
			printf("%f ",w3[i]);
	//printf("\n");
	}
	/*w1[0][0]=0.4;
	w1[0][1]=0.4;
	w1[0][2]=0.6;
	w1[0][3]=0.7;

	w1[1][0]=0.8;
	w1[1][1]=0.5;
	w1[1][2]=0.7;
	w1[1][3]=0.35;

	w1[2][0]=0.2;
	w1[2][1]=0.8;
	w1[2][2]=0.9;
	w1[2][3]=0.4;

	w3[0]=0.16;
	w3[1]=0.25;
	w3[2]=0.38;*/
	
	//printf("\n\n\n");

	float w2[4]={0.5 ,0.1, 0.8, 0.4};
	
	float bias1=0.2,bias2=1,eta=0.1;
	float *p,error[100],*F;
	float FinalWeight[row*column][20];
	float padded_matrix[row+1][column+1],w31[3];

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

	printf("printing input\n");
	for(i=0;i<=row+1;i++)
	{
		for(j=0;j<=column+1;j++){

		}
			// printf("%f ",input_new[i][j]);
		// printf("\n");
	}

	// printf("\n\n\n");

	printf("printing output\n");
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
			printf("%f ",output[i][j]);
		printf("\n");
	}
	//printf("\n\n\n");
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
		{
			count++;
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
						patch[c][d]=input_new[k+c][l+d];
						
					}
			}
			//printf("count=%d\n",count);
			/*for(p_1=0;p_1<3;p_1++)
			{
				for(p_2=0;p_2<3;p_2++)
				printf("%f ",patch[p_1][p_2]);
			printf("\n");
			}
			printf("\n\n\n"); */
	//		printf("printing initial weights\n");
			int in1,in2;
	
			F=miniCNN(patch,output[index1][index2],w1,w2,w3,bias1);
	//		printf("CNN\n");
			for(mn=0;mn<20;mn++){
				//printf("%f ",F[mn]);
				FinalWeight[count][mn]=F[mn];
				demo_wt[mn]=F[mn];
				}
			//	printf("\n");
			predicted_output[i][j]=predict(patch,demo_wt);
		//	printf("%f\n",predicted_output[i][j]);
			int count_v=-1,iter2=0;
			iter=0;
			float p1;
			p1=predicted_output[i][j];
			while((fabs(predicted_output[i][j]-(float)output[index1][index2])>0.0100) )
			{
				iter++;
		//		printf("%d %f %d\n",iter,fabs(predicted_output[i][j]-(float)(output[index1][index2])),count);
				count_v=-1;
				for(it1=0;it1<3;it1++)
				for(it2=0;it2<4;it2++){
				count_v++;
				w11[it1][it2]=F[count_v];
				}
				for(it1=0;it1<4;it1++){
				count_v++;
				w21[it1]=F[count_v];
				}
				for(it1=0;it1<4-1;it1++){
				count_v++;
				w31[it1]=F[count_v];
				}
				bias11=F[19];
				F=miniCNN(patch,output[index1][index2],w11,w21,w31,bias11);
				for(mn=0;mn<20;mn++){
				FinalWeight[count][mn] =F[mn];
				demo_wt[mn]=F[mn];
				}
				predicted_output[i][j]=predict(patch,demo_wt);
				if(p1==predicted_output[i][j])
				{
					p1=predicted_output[i][j];
					iter2++;
				}
				if(iter2>10000)
				break;	
				if((fabs(predicted_output[i][j]-(float)(output[index1][index2])))>(fabs(output[index1][index2]-p1)))
				{
					predicted_output[i][j]=p1;
					break;
				}
				p1=predicted_output[i][j];
			}
		//	printf("%d %f\n",count,predicted_output[i][j]);
			iterations[count]=iter;
			predicted_output[i][j]=predict(patch,demo_wt);
			free(F);
		}
	}
	//free(F);
	count=-1;
	printf("Printing Final\n");
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++){
			count++;
		//printf("%f %f %d\n ",output[i][j],predicted_output[i][j],iterations[count]);
	}
		//printf("\n");
	}
	
	//return(FinalWeight);
	printf("printing final weights\n");
	
	for(i=0;i<row*column;i++)
	{
		for(j=0;j<20;j++)
		{
			fprintf(fp,"%f ",FinalWeight[i][j]);
		}
		fprintf(fp,"\n");
	}
	fclose(fp);
}
float *miniCNN(float patch[3][3],int p,float w1[3][4],float w2[4],float w3[3],float bias1)
{
	//printf("\n\nminiCNN\n\n");

	int count=-1,k,l,c,d,q,r,i,j,count2,count3;
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
	if (argc != 2) 
        {
        	printf("Wrong parameters. Usage: ./cnn_prediction [iteration number]\n");
		return 1;
	}
        sscanf(argv[1], "%d", &ITER);
        printf("ITER : %d\n", ITER);

	float patch_1[3][3],t,input[row][column],output[row][column];
	time_t tm;
	srand((unsigned) time(&tm));
	int i,j,d,f;
	printf("hello\n");
	FILE *f1,*f2;
	char buffer[100];
	sprintf(buffer,"/media/srija/Seagate Backup Plus Drive/images/pie_jpg/experiments/p%d_im0.txt",ITER );
	
	f1=fopen("/media/srija/Seagate Backup Plus Drive/images/pie_jpg/experiments/temp_45.txt","r");
	f2=fopen(buffer,"r");
	
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
		{
			fscanf(f1,"%d",&f);
			// printf("%d ",f);
			input[i][j]=f;
		}
	}

	printf("\n");
	for(i=0;i<row;i++)
	{
		for(j=0;j<column;j++)
		{
			fscanf(f2,"%d",&d);
			// printf("%d ",d);
			output[i][j]=d;
		}
	}

	fclose(f1);
	fclose(f2);

	CNN(input,output,row,column, ITER);
	printf("printed\n");
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
}

