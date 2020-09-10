#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Author: Joseph Pietroluongo
// PID: 5901749
// I affirm that I wrote this program myself without any help
// from any other people or sources from the internet
// Summary:  find the count of the number of words in the file
//           and sort them lexicographically (ASCII order)

#define n 10000
#define OUT 0
#define IN 1

//prints usage
void usage(){
      printf:("Usage: mywords [-cs] [-f substring] filename\n");
}

//ASCII sorting method
void wordSorting(char *str1, int numberOfWords){

//Loop variables
      int i = 0; 
      int j = 0; 
      int k = 0;

      //sets up arrays
      char temp[100], *fstr, str[80][60];
      fstr = strtok(str1, " ,.-");
    
      while (fstr != NULL){
            strcpy(str[k], fstr);
            fstr = strtok(NULL, " ,.-");
            k++;
      }

      for (i = 1; i < numberOfWords; i++){
            for (j = 1; j <= numberOfWords - i; j++){
                  if (strcmp(str[j - 1], str[j])>0){
                        strcpy(temp, str[j - 1]);
                        strcpy(str[j - 1], str[j]);
                        strcpy(str[j], temp);
                  }
            }
      }
      printf("ASCII Sorted Order:\n");

      for (i = 0; i < numberOfWords; ++i){
            puts(str[i]);
      }

      printf(" ");
}

//method for couting how many words appear 
unsigned wordCount(char *str){
    
      int state = OUT;
      unsigned wordcount = 0;

      while (*str){
            if (*str == ' ' || *str == '\n' || *str == '\t'){
                  state = OUT;
            }
            else if (state == OUT){
                  state = IN;
                  ++wordcount;
            }
            ++str;
      }
      return wordcount;
} 

//method for the frequency of words in the array
void wordFrequency(char *word, char *allWords){
      int p = 0; 
      int q = 0;
      int numTimes = 0;
      int wordLength;
      wordLength = strlen(word);

      while (allWords[p] != '\0'){
            if (allWords[p] == word[q]){
                  while (allWords[p] == word[q] && allWords[p] != '\0'){
                        p++;
                        q++;
                  }

                  if (q == wordLength && (allWords[p] == ' ' || allWords[p] == '\0')){
                        numTimes++;
                  }
            }

            else{
                  while (allWords[p] != ' ') {
                        p++;
                        if (allWords[p] == '\0')
                        break;
                  }
            }
            p++;
            q = 0;
      }

      if (numTimes > 0){
            printf(" '%s' appears %d times", word, numTimes);
      }

      else{
            printf(" '%s' did not appear.", word);
      }
}

//Standard main method that sets up arguements
int main(int argc, char *argv[]){
      int opt;
      char buff[n];
      size_t read;
      int numOfWords;
      FILE *file;

      if(argc == 6){
            file = fopen(argv[5], "r");
      }

      else if(argc == 5){
            file = fopen(argv[4], "r");
      }

      else if(argc == 4){
            file = fopen(argv[3], "r");
      }

      else if(argc == 3){
            file = fopen(argv[2], "r");
      }

      else{
            file = fopen(argv[2], "r");
      }

      if (file){           
            printf("Contents: \n");
            while ((read = fread(buff, 1, sizeof buff, file)) > 0)
                  fwrite(buff, 1, read, stdout);

            if (ferror(file)){
                  printf("Error");
            }

            fclose(file);
            
            //set up case statement
            while ((opt = getopt(argc, argv, "csf:")) != -1){
                  numOfWords = wordCount(buff);

                  switch (opt){
                       
                  case 's':
                        wordSorting(buff, numOfWords);
                        break;
                            
                  case 'c':
                        printf("Number of words: %d\n", numOfWords);
                        break;
                        
                  case 'f':
                        printf("Substring: %s\n", optarg);
                        wordFrequency(optarg, buff);
                        break;

                  defualt:
                        printf("Unknown case: %c\nPlease check usage\n", optopt);
                        usage();
                        break;
                  }
            }     
      }
      return 0;
}