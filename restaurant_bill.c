#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct items
{
    char item[20];
    float price;
    int qty;
};

struct orders
{
    char customer[50];
    char date[50];
    int numofitems;
    struct items itm[50];
};

//functions to generate bills
int generateBillHeader(char name[50],char date[30])
{
    printf("\n\n");
    printf("\t  Hiradnya Restaurant");
    printf("\n--------------------------------------");
    printf("\nDate:%s",date);
    printf("\nInvoice To: %s",name);
    printf("\n");
    printf("--------------------------------------\n");
    printf("Items\t\t");
    printf("Qty\t\t");
    printf("Total\t\t");
    printf("\n--------------------------------------");
    printf("\n\n");
}
int generateBillBody(char item[30],int qty,float price)
{
    printf("%s\t\t",item);
    printf("%d\t\t",qty);
    printf("%.2f\t\t",qty*price);
    printf("\n");
}


int generateBillFooter(float total)
{
    printf("\n");
    float dis=0.1*total;
    float netTotal=total-dis;
    float cgst=0.09*netTotal,grandTotal=netTotal+2*cgst;    //nettotal + cgst + sgst
    printf("--------------------------------------\n");
    printf("Sub Total\t\t\t%.2f",total);
    printf("\nDiscount\t\t\t%.2f",dis); // ************
    printf("\n\t\t\t\t-------");
    printf("\nNet Total\t\t\t%.2f",netTotal);
    printf("\nCGST @9%s\t\t\t%.2f","%",cgst);
    printf("\nSGST @9%s\t\t\t%.2f","%",cgst);
    printf("\n--------------------------------------");
    printf("\nGrand Total\t\t\t%.2f",grandTotal);
    printf("\n--------------------------------------\n");
}

int main()
    {
        int opt,n;
        struct orders ord;
        struct orders order;
        char saveBill='y';
        char name[50];
        FILE *fp;
        //dashboard
        while(1)
        {
            float total=0;
            int invoiceFound=0;
            printf("\n============Hiradnya Restaurant============");
            printf("\n\nPlease select your prefered operaton");
            printf("\n\n1.Generate Invoice");
            printf("\n2.Show all Invoices");
            printf("\n3.Search Invoices");
            printf("\n4.Exit");


            printf("\n\nYour Choice:\t");
            scanf("%d",&opt);
            switch(opt)
            {
                case 1: 
                printf("\nPlease enter the name of customer:\t");
                scanf("%s",&ord.customer);
                strcpy(ord.date,__DATE__);               //****************
                printf("\nPlease enter the number of items:\t");
                scanf("%d",&n);
                ord.numofitems=n;
                for(int i=0;i<n;i++)
                {
                    printf("\n\n");
                    printf("Please enter the item %d:\t",i+1);
                    scanf("%s",&ord.itm[i].item);
                    printf("Please enter the quantity:\t");
                    scanf("%d",&ord.itm[i].qty);
                    printf("Please enter the unit price:\t");
                    scanf("%f",&ord.itm[i].price);
                    total +=ord.itm[i].qty*ord.itm[i].price;
                }

                generateBillHeader(ord.customer,ord.date);
                for(int i=0;i<ord.numofitems;i++)
                {
                    generateBillBody(ord.itm[i].item,ord.itm[i].qty,ord.itm[i].price);
                }

                generateBillFooter(total);
                printf("\nDo you want to save the invoice[y/n]:\t");
                scanf("%s",&saveBill);

                if(saveBill=='y')
                {
                    fp=fopen("RestaurantBill.dat","a+");
                    fwrite(&ord,sizeof(struct orders),1,fp);
                    if(fwrite!=0)
                    printf("\nSuccessfully Saved");
                    else
                    printf("\nError Saving");
                    fclose(fp);
                }
                break;

                case 2:
                fp=fopen("RestaurantBill.dat","r");
                printf("\n*****Your Previous Invoices*****\n");
                while (fread(&order,sizeof(struct orders),1,fp))
                {
                float tot=0;
                generateBillHeader(order.customer,order.date);
                for(int i=0;i<order.numofitems;i++)
                {
                    generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                    tot+=order.itm[i].qty*order.itm[i].price;
                }
                generateBillFooter(tot);
                }
                fclose(fp);
                break;

                case 3:
                printf("Enter the name of the customer:\t");
                scanf("%s",&name);
                fp=fopen("RestaurantBill.dat","r");
                printf("\t*****Invoice of %s*****",name);
                while (fread(&order,sizeof(struct orders),1,fp))
                {
                    float tot=0;
                    if(!strcmp(order.customer,name))
                    {
                        generateBillHeader(order.customer,order.date);
                        for(int i=0;i<order.numofitems;i++)
                        {
                            generateBillBody(order.itm[i].item,order.itm[i].qty,order.itm[i].price);
                            tot+=order.itm[i].qty*order.itm[i].price;
                        }
                        generateBillFooter(tot);
                        invoiceFound=1;
                    }

                }
                
                if(!invoiceFound)
                {
                    printf("Sorry the invoice for %s does not exists",name);
                }
                fclose(fp);
                break;

                case 4:
                printf("\n\t\t Bye Bye :)\n\n");
                exit(0);
                break;

                default:
                printf("Sorry invalid option");
                break;
                
            }
            printf("\n\t\t Bye Bye :)\n\n");
            printf("/n/n");

            
        }

        return 0;
        
    }
