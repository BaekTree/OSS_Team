

void Quiz(country_t *country){
    
    char answer[50];

    int number_of_quiz_question = 10;
    int number_of_countries = 18;
    int score = 0;

    srand(time(NULL));

    int array[number_of_countries];

    for (int i = 0; i < number_of_countries; i++) {     // fill array
    array[i] = i;
    }


    for (int i = 0; i < number_of_countries; i++) {    // shuffle array
        int temp = array[i];
        int randomIndex = rand() % number_of_countries;

        array[i]  = array[randomIndex];
        array[randomIndex] = temp;
    }


    for(int i=0; i<number_of_quiz_question; i++){
        
        int n = array[i];
        int q= rand()%2+1;

        printf("%d. ", i+1);

        if(q==1){
            printf("Which country has the capital %s?\n", country[n].capital_name);
            scanf("%s", &answer);

            if(strcmp(answer, country[n].country_name)!=0){
                printf("Correct Answer!!\n");
                score++;
            }
            else if(strcmp(answer, "quit")!=0){
                break;
            }
            else{
                printf("Wrong Answer!!\n");
            }

        }
        if(q==2){
            printf("What is the capital of %s?\n", country[n].country_name);
            scanf("%s", &answer);

            if(strcmp(answer, country[n].capital_name)!=0){
                printf("Correct Answer!!\n");
                score++;
            }else if(strcmp(answer, "quit")!=0){
                break;
            }
            else{
                printf("Wrong Answer!!\n");
            }
        }

    }
    printf("\n\nYour score is %d", score);
    
}
