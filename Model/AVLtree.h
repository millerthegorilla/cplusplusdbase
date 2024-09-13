/**********************************************************/
/*              Programmed by Gerard Monells              */
/*               gerardmonells@hotmail.com                */
/**********************************************************/

#pragma once

#ifndef _AVLTREE_H_
#define _AVLTREE_H_

#include <iostream>
#include <fstream>
#include <typeinfo>
#include <string>
#include <stdlib.h>
#include "record.h"
#include "..\Params.h"
#include "SearchObject.h"
#include "SearchStruct.h"

class SearchObject;

typedef unsigned int uint;

class tree
{
public:

	virtual void add_item(int x, Records::record * rec){};
	virtual void inorder(){};
	virtual std::string GetFieldName() const { return "";};
	virtual bool save(std::ifstream & fout){return true;};
	virtual bool read(std::ifstream & fin){return true;};
	virtual ~tree(){};
	TREETYPE my_type;

};

template <typename T>
class AVLtree : public tree
{

public:
  AVLtree();
  AVLtree(const AVLtree<T>& a);
  AVLtree<T>& operator=(const AVLtree<T>& a);
 
  virtual void add_item(T x, Records::record * rec, int fieldnum);
  void search(SearchObject &searchObj);
  void preorder();
  virtual void inorder();
  void postorder();
  virtual bool save(std::ofstream & fout);
  virtual bool read(std::ifstream & fin); 
  void delete_item(T * x);
  virtual ~AVLtree();
  
  uint size();
  void SetFieldNum(int num){ field_num = num; }
  void SetFieldName(std::string name) { field_name = name; }
  std::string GetFieldName () const { return field_name; }
protected:
	struct node 
	{
		node(T x, node* l, node* r, uint h, Records::record * rec = NULL, int fieldnumber = 0)
		{
			  item = x;
			  rec->setfieldpointer(&item, fieldnumber);
			  _rec = rec;
			  left = l;
			  right = r;
			  height = h;
		}
		Records::record * _rec;
		T item;
		node* left;
		node* right;
		uint height;
	};

  node* root;
  uint num_nodes;
  int field_num;
  std::string field_name;

  node* copy_nodes(node *n);
  void destroy_nodes(node *n);
  node* add_node(node* n, T x, Records::record * rec, int fieldnum);
  uint maxof(uint a, uint b);
  uint height(node* n);
  node* rotate_left(node* n);
  node* rotate2_left(node* n);
  node* rotate_right(node* n);
  node* rotate2_right(node* n);
  void search(node* n, T term, HANDLE mutex, std::vector<int> &recordvector);
  void preorder(node* n);
  void inorder(node* n);
  void postorder(node* n);
  void type_me();
  bool save(node *n, std::ofstream &fout);
  node* getparent(T * key);
  node* getnode(T * key);
  int balance(node *t);
  node* getinordersuccessor(node *t);
  void remove(T * key);
  int getheight(node *t);
   
};



#endif