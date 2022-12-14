# CS225-Final-Project

## About the Project:

Our leading question for this project was the following: given a dataset of Netflix movies/shows/motion pictures, what movies are most similar to a movie provided by the user in regards to characteristics provided by the user? For example, one query the user can make is what movie is most similar to Black Panther in regards to level of popularity, which is numerically measured by how many people watched or the amount of the revenue generated. The output is a list of top x movies that are most similar to what the user’s query is. 
  
## Built With: 

  Main Programming Languages/Frameworks: C++, Catch Hpp Testing Framework 
  
## GitHub Organization:
  Our repository can be found at this link: https://github.com/madebayo1023/CS225-Final-Project. 
  The code can be found in the folder labeled "src."
  The tests can be found in "test.cpp" in the folder labeled "test."
  The data can be found in the folder labeled "data."
  The written report can be found on our repo. Look for the file titled "results.md."
  The presentation video is here: https://mediaspace.illinois.edu/edit/1_i4dnjnjh 

## Prerequisites/Installation:
  Make sure to have Visual Studio Code installed.

  Create your own directory ("bin") using the command "mkdir bin." This is where your executable will lie once your program has been linked. 

### To run the code:

1. Define your input data by passing the correct file path to your dataset, preferably a CSV file, into the Recommendation constructor. The current CSV file is delimited by commas with the following attributes: title, year, certificate, duration, genre, rating, description, stars, and votes. 
2. Call any method you would like on the object instantiated in step 4 and observe its output in the terminal after using "make exec" to compile the program. 
3. To run the executable, do "./bin/exec."

### To create and run your own, personalized tests:

1. Run the command "make test". 
2. Run any specific test case using the command "./bin/tests 'TestName'" or "./bin/tests" to run all tests.
3. Ensure the output matches the required test case and ensure the test case passes. 

## Acknowledgements 

1. Kaggle Dataset: https://www.kaggle.com/datasets/victorsoeiro/netflix-tv-shows-and-movies
