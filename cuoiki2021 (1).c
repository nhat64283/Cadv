#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "jrb.h"
#include "jval.h"
#include "dllist.h"

#define INFINITIVE_VALUE 9999.0

typedef struct {
	JRB edges;
	JRB vertices;
} Graph;

Graph createGraph();
void dropGraph(Graph graph);
void addVertex(Graph graph, int id, char *name);
void addEdge(Graph graph, int v1, int v2, double weight);
double getEdgeValue(Graph graph, int v1, int v2);
char *getVertex(Graph graph, int id);
int hasEdge(Graph graph, int v1, int v2);
int indegree(Graph graph, int v, int *output);
int outdegree(Graph graph, int v, int *output);
double shortestPath(Graph graph, int s, int t, int *path, int *length);
int getNumOfV(Graph graph);
int getNumOfE(Graph graph);
int c_to_n(char c);
int main() {

	int choice, numOfV, numOfE, id1, id2, total, j, max, s, t, length;
  //
  char str[50],str1[100];
	int output[100], path[100], output1[100];
  int res,num,res1;
  int k = 0;
  char m1,m2;
	double w, weight;
	FILE *f;

	Graph graph = createGraph();

	do {
    printf("\n1.In ra danh sach\n");
		printf("2.Kiem tra tiep xuc gan\n");
		printf("3.In ra danh sach tiep xuc gan\n");
		printf("4.Danh sach tiep xuc gan voi nhieu nguoi nhat\n");
    printf("5.Danh sach F1 va F2\n");
		printf("10.Thoat\n");
		printf("Lua chon cua ban: ");
		scanf("%d", &choice);
		switch(choice)  {
			case 1:
         f = fopen("tiepXucGan.txt","r");
                if (f == NULL) {
                    printf("Khong the mo file\n");
                    return (-1);
                }
                fgets(str,50,f);
                int i = atoi(str);
                numOfV = i;
                printf("%d\n",i);
                while(fgets(str,50,f) != NULL) {
                    char *token,*token1,*token2;
                    
                    token1 = strtok(str," ");
                    char m = token1[0];
                    int num1 = c_to_n(m);
                    //printf("%d ",num1);
                    printf("%s",token1 );
                    addVertex(graph, num1, token1);
                    while(token1 != NULL) {
                        token2 = strtok(NULL," ");
                        
                        if(token2 == NULL)
                            break;
                        char n = token2[0];
                         int num2 = c_to_n(n);
                        printf(" %s", token2);
                        addEdge(graph,num1,num2,1);
                    }
                    printf("\n");
                }


				break;
			case 2:
        
        printf("Nhap ten nguoi 1 : "); 
        scanf("%s",&m1); 
        
        //
        printf("Nhap ten nguoi 2 : "); 
        scanf("%s",&m2);
        int num1 = c_to_n(m1);
        int num2 = c_to_n(m2);
        if (hasEdge(graph, num1, num2)) {
				printf("2 nguoi nay co tiep xuc voi nhau\n");
				break;
			}
      printf("2 nguoi nay khong co tiep xuc voi nhau\n");
				break;
			case 3:
        printf("Nhap ten nguoi 1 : "); 
        scanf("%s",&m1); 
         num = c_to_n(m1);
        res = outdegree(graph, num, output);
        printf("Danh sach tiep xuc gan cau nguoi do la:\n");
        for(int i =0; i<res; i++){
          printf(" %s\n", getVertex(graph, output[i]));
        }
				break;
			case 4:
      max =0;
			
			for(int i= 0; i< numOfV; i++)
      {
        if(max < outdegree(graph, i, output))
        {
          max = outdegree(graph, i, output);
          output1[i] = i;
        }
      }
        //res=3 output=[2,3,6]
			printf("So luong nguoi da tiep xuc la:%d\n", max);
				for (int i = 0; i < numOfV; i++) {
					if (max == outdegree(graph, i, output)) {
						printf(
							"Nguoi tiep xuc voi nhieu nguoi nhat la:%s\n", getVertex(graph, output1[i]));
					}
				}
			
			break;
				break;
      case 5:
        printf("Nhap ten F0 : "); 
        scanf("%s",&m1); 
        num = c_to_n(m1);
        res = outdegree(graph, num, output);
        printf("Danh sach F1 la:\n");
        for(int i=0;i<res;i++){
          printf("%s ",getVertex(graph, output[i]));
        }
        printf("\nDanh sach F2 la:\n");
        // for(int i =0;i<res;i++){
        //     res1 = outdegree(graph, output[i], output1);
        //     for(int j=0;j<res1;j++){
        //     printf("%s ",getVertex(graph, output1[i]));
        // }
        // }
        break;
      case 6:
        break;
      case 7:
        break;
      case 8:
        break;
      case 9:
        break;
			case 10:
				break;

			default:
          printf("Ban da nhap sai! Moi ban nhap lai!\n");
				break;

		}
	} while(choice != 10);

	return 0;
}

Graph createGraph()
{
    Graph graph;

    graph.edges = make_jrb();
    graph.vertices = make_jrb();

    return graph;
}

void dropGraph(Graph graph)
{
    JRB node, tree;

    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        jrb_free_tree(tree);
    }
    jrb_free_tree(graph.edges);
    jrb_free_tree(graph.vertices);
}

void addVertex(Graph graph, int id, char *name)
{
    JRB node = jrb_find_int(graph.vertices, id);

    if (node == NULL)
        jrb_insert_int(graph.vertices, id, new_jval_s(strdup(name)));
}

void addEdge(Graph graph, int v1, int v2, double weight)
{
    JRB node, tree;
    if (!hasEdge(graph, v1, v2))
    {
        //add v1->v2
        node = jrb_find_int(graph.edges, v1);
        if (node == NULL)
        {
            tree = make_jrb();
            jrb_insert_int(graph.edges, v1, new_jval_v(tree));
        }
        else
        {
            tree = (JRB)jval_v(node->val);
        }
        jrb_insert_int(tree, v2, new_jval_d(weight));
        //add v2->v1
        node = jrb_find_int(graph.edges, v2);
        if (node == NULL)
        {
            tree = make_jrb();
            jrb_insert_int(graph.edges, v2, new_jval_v(tree));
        }
        else
        {
            tree = (JRB)jval_v(node->val);
        }
        jrb_insert_int(tree, v1, new_jval_d(weight));
    }
}

double getEdgeValue(Graph graph, int v1, int v2)
{
    JRB node, tree, node1;

    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
        return INFINITIVE_VALUE;
    tree = (JRB)jval_v(node->val);
    node1 = jrb_find_int(tree, v2);

    if (node1 == NULL)
        return INFINITIVE_VALUE;

    return jval_d(node1->val);
}

char *getVertex(Graph graph, int id)
{
    JRB node = jrb_find_int(graph.vertices, id);

    if (node == NULL)
        return NULL;
    else
        return jval_s(node->val);
}

int hasEdge(Graph graph, int v1, int v2)
{
    JRB node, tree;

    node = jrb_find_int(graph.edges, v1);
    if (node == NULL)
        return 0;
    tree = (JRB)jval_v(node->val);
    if (jrb_find_int(tree, v2) == NULL)
        return 0;
    else
        return 1;
}

int indegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total = 0;
    jrb_traverse(node, graph.edges)
    {
        tree = (JRB)jval_v(node->val);
        if (jrb_find_int(tree, v))
        {
            output[total] = jval_i(node->key);
            total++;
        }
    }
    return total;
}

int outdegree(Graph graph, int v, int *output)
{
    JRB tree, node;
    int total = 0;

    node = jrb_find_int(graph.edges, v);

    if (node == NULL)
        return 0;

    tree = (JRB)jval_v(node->val);

    jrb_traverse(node, tree)
    {
        output[total] = jval_i(node->key);
        total++;
    }
    return total;
}

double shortestPath(Graph graph, int s, int t, int *path, int *length)
{
    double distance[1000], min, w, total;
    int previous[1000], tmp[1000], visited[1000];
    int n, output[100], i, v, u;
    Dllist queue, ptr, node;

    for (i = 0; i < 1000; i++)
    {
            distance[i] = INFINITIVE_VALUE;
            visited[i] = 0;
            previous[i] = 0;
    }
    distance[s] = 0;
    previous[s] = s;
    visited[s] = 1;

    queue = new_dllist();
    dll_append(queue, new_jval_i(s));

    while(!dll_empty(queue))
    {
        min = INFINITIVE_VALUE;
        dll_traverse(ptr, queue)
        {
            u = jval_i(ptr->val);
            if(min > distance[u])
            {
                min = distance[u];
                node = ptr;
            }
        }
        u = jval_i(node->val);
        visited[u] = 1;
        dll_delete_node(node);

        if(u == t)
            break;

        n = outdegree(graph, u, output);

        for (i = 0; i < n; i++)
        {
            v = output[i];
            w = getEdgeValue(graph, u, v);
            if( distance[v] > distance[u] + w)
            {
                distance[v] = distance[u] + w;
                previous[v] = u;
            }
            if(visited[v] == 0)
                dll_append(queue, new_jval_i(v));
        }
    }

    total = distance[t];
    if(total != INFINITIVE_VALUE)
    {
        tmp[0] = t;
        n = 1;
        while(t != s)
        {
            t = previous[t];
            tmp[n++] = t;
        }

        for (i = n - 1; i >= 0; i--)
        {
            path[n - i - 1] = tmp[i];
        }
        *length = n;
    }

    return total;
}

int getNumOfV(Graph graph)
{
    JRB node;
    int total = 0;

    jrb_traverse(node, graph.vertices)
        total++;

    return total;
}

int getNumOfE(Graph graph)
{
    JRB node1, node2;
    int total = 0;

    jrb_traverse(node1, graph.vertices)
        jrb_traverse(node2, graph.vertices) if (hasEdge(graph, jval_i(node1->key), jval_i(node2->key)))
            total++;

    return total;
}
int c_to_n(char c)
{
    int n = -1;
    static const char * const alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char *p = strchr(alphabet, toupper((unsigned char)c));

    if (p)
    {
        n = p - alphabet;
    }

    return n;
}