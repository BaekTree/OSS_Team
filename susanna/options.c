void Options(){
	
    int option;
    char Input[100];

    
    int i=0;
	
    printf("\n\nChoose the information you would like to see");
    printf("\n\t 1 : List the country names according to the continent");
	printf("\n\t 2: List the information of a country");
	printf("\n\t 3 : List the countries according to the GDP");
	printf("\n\t 4 : Test your Knowledge (Quiz)");
    printf("\n\t 0: Quit the application");
	printf("\n");
    
    while(1){
	    scanf("%d", &option);

        switch(option){
            case 1: 
                printf("Enter the name of the continent you would like to see\n");
                scanf("%s", Input);
                //CountryNamesList(Input);
                break;

            case 2:
                 printf("Enter the country name you would like to see\n");
                scanf("%s", Input);
                //CountryInformation(Input);
                 break;

            case 3: 
                
                break;

            case 4: 
                Quiz();
                break;

            case 0:
                printf("Application is closed\n"); 
                exit(0);

            default: 
                printf("You have entered a wrong value\n"); 
                break;

        }
    }
}
