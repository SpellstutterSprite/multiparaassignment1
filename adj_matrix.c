/**
 * FILE: ADJ_MATRIX.C
 * 
 * THIS FILE  CONTAINS EMPTY / DO-NOTHING IMPLEMENTATIONS
 * FOR THE FUNCTIONS REQUIRED FOR THE ADJACENCY MATRIX STRUCT. 
 *
 * DO NOT RENAME THESE FUNCTIONS OR CHANGE THEIR RETURN
 * TYPES OR INPUT PARAMETERS.
 *
 * YOU NEED TO COMPLETE THE IMPLEMENTATION OF THESE
 * FUNCTIONS. 
 *
 * THESE FUNCTIONS RECEIVE INPUT PARAMETERS THAT WILL
 * PROVIDE THEM WITH THE INFORMATION THEY REQUIRE. 
 *
 * THE FUNCTIONS RETURN VALUES TO REPRESENT SUCCESS, ERROR,
 * OR, IN SOME CASES, DATA THAT HAS TO BE RETURNED. THE CALLER 
 * OF THESE FUNCTIONS WILL EXPECT TO RECEIVE THESE RETURN VALUES 
 * IN ORDER TO VERIFY THE OUTCOME OF THE FUNCTION CALL. 
 *
 * IF THERE ARE ANY FUNCTIONS THAT YOU DON'T HAVE TIME TO 
 * IMPLEMENT, PLEASE LEAVE THE EMPTY / DO-NOTHING IMPLEMENTATION
 * FOR THEM IN THIS FILE, OTHERWISE YOUR PROGRAM WON'T COMPILE
 * WHEN IT IS FED INTO OUR TESTER PROGRAM.
 * 
 */

/** 
 * ### INCLUDES
 */
#include "core_definitions.h"
#include "my_malloc.h"          // gives access to memory allocation functions, including 'myMalloc'
#include <stdio.h>              // required for access to file input-output functions in C
#include "adj_matrix.h"         // required, to include the Adjacency Matrix data structures and function declarations
                                // that are being implemented in this file
#include <stdbool.h>            // required, to include the definition of the 


/** #### FUNCTION IMPLEMENTATIONS ## */

/**
 * Create a new, empty Adjacency Matrix, returning a pointer to the newly 
 * allocated matrix OR a value of NULL in the event of error. Ensure that 
 * the matrix is initialised to the defaultEdgeValue provided.
 * 
 * Remember to use myMalloc() to allocate memory instead of malloc(). 
 * In the event of memory allocation errors, return a value of NULL
 * for this function instead of the usual MEMORY_ALLOCATION_ERROR
 *
 */
AdjacencyMatrix* createAdjacencyMatrix(int defaultEdgeValue)
{
  ///allocates memory then checks for success 
  AdjacencyMatrix* pMatrix = (AdjacencyMatrix*)myMalloc(sizeof(AdjacencyMatrix));
  
  if (pMatrix == NULL)
  {
    return NULL;
  }

  ///initializes all elements of the matrix 
  for (int i = 0; i < NUMBER_OF_VERTICES; i++)
  {
    for (int j = 0; j < NUMBER_OF_VERTICES; j++)
    {
      pMatrix->matrix[i][j] = defaultEdgeValue;
    }
  }
  return pMatrix;
}

/**
 * Add a new edge into an Adjacency Matrix using the details given
 * e.g., source node (src), destination node (dest), and weight
 * of the edge.
 * 
 * The function should return SUCCESS or a relevant error code.
 */
int addEdge(AdjacencyMatrix *pMatrix, int src, int dest, int weight)
{
  ///checks all inputs are valid then adds an edge if they are, unsure my validation is optimal here but I couldn't think of a better way to do it
  if (pMatrix == NULL)
  {
    return INVALID_INPUT_PARAMETER;
  }

  if (src < 0 || src >= NUMBER_OF_VERTICES)
  {
    return INVALID_INPUT_PARAMETER;
  }

  if (dest < 0 || dest >= NUMBER_OF_VERTICES)
  {
    return  INVALID_INPUT_PARAMETER;
  }
  
  if (weight < 0)
  {
    return INVALID_INPUT_PARAMETER;
  }

  pMatrix ->matrix[src][dest] = weight;
  return SUCCESS;
}

/**
 * This function should add a collection of new edges into an 
 * AdjacencyMatrix using the input values given. In this case,
 * an array of Edges is provided, each one containing details of
 * a single Edge in the graph (src node, dest node, and weight).
 * 
 * You need to consider validation of the edges as you work your
 * way through them. The function should return SUCCESS if all
 * edges were processed successfully. It should return PARTIAL_SUCCESS
 * if only some of the edges were processed successfully. It should
 * return INVALID_INPUT_PARAMETER if all edges in the array were
 * found to be invalid. Your function should attempt to process all
 * edges before returning the result, ignoring any that are invalid,
 * but ensuring any valid edges are added to the graph successfully.
 * 
 */
int addEdges(AdjacencyMatrix *pMatrix, Edge edges[], int edgeNum)
{ 
  /// validates the inputs initially to make sure they exist
  if (pMatrix == NULL)
  {
    return INVALID_INPUT_PARAMETER;
  }

  if (edges == NULL)
  {
    return INVALID_INPUT_PARAMETER;
  }

  if (edgeNum <= 0)
  {
    return INVALID_INPUT_PARAMETER;
  }

  int workingEdges = 0;

  ///validates inputs then either continues the loop on invalid ones or adds the edge on valid ones
  for (int i = 0; i < edgeNum; i++)
  {
    int src = edges[i].src;
    int dest = edges[i].dest;
    int weight = edges[i].weight;

    if (src < 0 || src >= NUMBER_OF_VERTICES)
    {
      continue;;
    }

    if (dest < 0 || dest >= NUMBER_OF_VERTICES)
    {
      continue;
    }

    if (weight < 0)
    {
      continue;
    }

    pMatrix ->matrix[src][dest] = weight;
    workingEdges++;
  }

  if (workingEdges == edgeNum)
  {
    return SUCCESS;
  }
  else if (workingEdges > 0) 
  {
    return PARTIAL_SUCCESS;
  }
  else
  {
    return INVALID_INPUT_PARAMETER;
  }
}

/**
 * This function will receive the name of a file on disk which contains the 
 * data for a graph which has been stored in the form of an adjacency matrix. 
 * The function should read the content from the file and use it to populate 
 * the AdjacencyMatrix provided. The file will be formatted thus:
 * 
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 0 0 0 0 0 0 0 0 0
 * 
 * I.e., assuming a graph with 10 vertices, this will require a 10 x 10 matrix.
 * 
 * Each line in the file represents the next row in matrix, indexed from 0 to 9.
 * 
 * Each line will record the weight of the relevant edge in the graph. This will
 * be a value of zero (no edge) or a value of greater than zero (signifying that
 * an edge does exist, and the weight of that edge).
 * 
 * The function should return SUCCESS or a relevant error code.
 * 
 */
int loadMatrixFromFile(AdjacencyMatrix *pMatrix, char filename[])
{
  /// validates inputs then opens adjacency_matrix.txt as read only
  if (pMatrix == NULL)
  {
    return INVALID_INPUT_PARAMETER;
  }

  if (filename == NULL)
  {
    return INVALID_INPUT_PARAMETER;
  }

  FILE* file = fopen(filename, "r");

  if (file == NULL)
  {
    return FILE_IO_ERROR;
  }

  /// loops through the grid on adjacentcy_matrix.txt and inputs the value into the corresponding spot of pmatrix each itteration
  for (int i = 0; i < NUMBER_OF_VERTICES; i++)
  {
    for (int j = 0; j < NUMBER_OF_VERTICES; j++)
    {
      int value;
      int readitems = fscanf(file, "%d", &value);
      
      if (readitems != 1)
      {
      fclose (file);
      return FILE_IO_ERROR;
      }

      pMatrix ->matrix[i][j] = value;
    }
  }
  fclose(file);

  return SUCCESS;
}




int doDepthFirstTraversal(AdjacencyMatrix *pMatrix, int startingNode, int traversalOutput[])
{ 
  ///validate inputs and set up data structures + their related variables
  if (pMatrix == NULL)
  {
    return INVALID_INPUT_PARAMETER;
  }

  if (traversalOutput == NULL)
  {
    return INVALID_INPUT_PARAMETER;
  }

  if (startingNode <0 || startingNode >= NUMBER_OF_VERTICES)
  {
    return INVALID_INPUT_PARAMETER;
  }
  
  int stack[NUMBER_OF_VERTICES];
  int outputIndex = 0;
  int current_node = startingNode;
  int visited[NUMBER_OF_VERTICES];
  int stackTop = -1;
  int continueTraversal = 1;
  
  for (int i = 0; i < NUMBER_OF_VERTICES; i++)
  {
    visited[i] = 0;
  }

  visited[current_node] = 1;
  traversalOutput[outputIndex] = current_node;
  outputIndex++;

  /// main loop following the method shown in the lectures, checks for unvisited neighbours, pushes the current node to the stack,
  /// to be able to backtrack, moves to the neighbouring node, marks that as being visited, then restarts. If no neighbouring node
  /// is found it tries to backtrack, then if backtrack stack is empty finishes the loop.
  while(continueTraversal)
  {
    int unvisitedNeighbour = 0;

    for (int i = 0; i < NUMBER_OF_VERTICES; i++)
    {
      if (pMatrix ->matrix[current_node][i] > 0)
      {
        if (visited[i] == 0)
        {
          stackTop++;
          stack[stackTop] = current_node;
          current_node = i;
          visited[current_node] = 1;
          traversalOutput[outputIndex] = current_node;
          outputIndex++;
          unvisitedNeighbour = 1;
          break;
        }
      }
    }

    if(!unvisitedNeighbour)
    {
      if (stackTop >= 0)
      {
        current_node = stack[stackTop];
        stackTop--;
      }
      else
      {
        continueTraversal = 0;
      }
    }
  }
  return SUCCESS;
}
