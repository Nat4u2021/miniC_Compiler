#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "ast.h"
#include <stack>
#include <iostream>
#include <cstring>
#include "semantic_analysis.h"

using namespace std;

bool check(vector<vector<char*>*> stackOfVectors, char* searchString) {
    for (vector<char*>* topVector: stackOfVectors) { // loop until stack is empty
        for (char* s : *topVector) { // loop through the elements of the top vector
            if (strcmp(s, searchString) == 0) { // if the search string is found in the top vector, return true
                return true;
            }
        }
    }
    return false; // if the search string was not found in any vector, return false
}

bool helper(vector<astNode*> nodes, vector<vector<char*>*> temp){
    bool result = true;

	while (!nodes.empty()){
		astNode* currnode = nodes.front();
		nodes.erase(nodes.begin());
	
		if (currnode->type == ast_stmt){
			if (currnode->stmt.type == ast_block){
				vector<char*> *currvector = new vector<char*>();
				temp.push_back(currvector);
				helper(*currnode->stmt.block.stmt_list, temp);
				temp.pop_back();
				delete(currvector);
			}
			else if (currnode->stmt.type == ast_decl){
				vector<char*> *currvector;
				currvector = temp.back();
				currvector->push_back(currnode->stmt.decl.name);
			}
			else if (currnode->stmt.type == ast_call){
				vector<astNode*> newnodes;
				if (currnode->stmt.call.param != NULL) newnodes.push_back(currnode->stmt.call.param);
				helper(newnodes, temp);	
			}
			else if (currnode->stmt.type == ast_ret){
				vector<astNode*> newnodes;
				newnodes.push_back(currnode->stmt.ret.expr);
				helper(newnodes, temp);	
						
			}
			else if (currnode->stmt.type == ast_while){
				vector<astNode*> newnodes;
				newnodes.push_back(currnode->stmt.whilen.cond);
				newnodes.push_back(currnode->stmt.whilen.body);
				helper(newnodes, temp);		
					
			}
			else if (currnode->stmt.type == ast_if){
				vector<astNode*> newnodes;
				newnodes.push_back(currnode->stmt.ifn.cond);
				newnodes.push_back(currnode->stmt.ifn.if_body);
				if (currnode->stmt.ifn.else_body != NULL) newnodes.push_back(currnode->stmt.ifn.else_body);
				helper(newnodes, temp);	
							
			}
			else if (currnode->stmt.type == ast_asgn){
				vector<astNode*> newnodes;
				newnodes.push_back(currnode->stmt.asgn.lhs);
				newnodes.push_back(currnode->stmt.asgn.rhs);
				helper(newnodes, temp);		
					
			}						
		}
		else if (currnode->type == ast_var){
			bool declared = check(temp, currnode->var.name);
			if (!declared){
				printf("ERROR: variable %s has not been declared\n", currnode->var.name);
				result = false;
			}
		}
		else if (currnode->type == ast_rexpr){
			vector<astNode*> newnodes;
			newnodes.push_back(currnode->rexpr.lhs);
			newnodes.push_back(currnode->rexpr.rhs);
			helper(newnodes, temp);
			
		}
		else if (currnode->type == ast_bexpr){
			vector<astNode*> newnodes;
			newnodes.push_back(currnode->bexpr.lhs);
			newnodes.push_back(currnode->bexpr.rhs);
			helper(newnodes, temp);
			
		}
		else if (currnode->type == ast_uexpr){
			vector<astNode*> newnodes;
			newnodes.push_back(currnode->uexpr.expr);
			helper(newnodes, temp);
			
		}
	}
	return result;
}

bool valid_semantic_analysis(astNode *root){
	bool valid = true;

	vector<vector<char*>*> symbol_table_stack;
	vector<char*> *currvector = new vector<char*> ();
	symbol_table_stack.push_back(currvector);

	if (root->func.param != NULL){
		currvector->push_back(root->func.param->var.name);
	}

	root = root->func.body;
	vector<astNode*> nodes = *root->stmt.block.stmt_list;

	valid = helper(nodes, symbol_table_stack);

	symbol_table_stack.pop_back();
	delete(currvector); 

	return valid;
}
