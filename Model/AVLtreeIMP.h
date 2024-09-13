#ifndef _AVLTREEIMP_H_
#define _AVLTREEIMP_H_

#include "AVLtree.h"
#include <string>
#include <math.h>
#include <assert.h>

template <typename T>
AVLtree<T>::AVLtree() {
  root = NULL;
  num_nodes = 0;
  type_me();
}

template <typename T>
AVLtree<T>::AVLtree(const AVLtree<T>& a) {
  root = copy_nodes(a.root);
  num_nodes = a.num_nodes;
  my_type = a.mytype;
}

template <typename T>
AVLtree<T>& AVLtree<T>::operator=(const AVLtree<T>& a) {
  destroy_nodes(root);
  root = copy_nodes(a.root);
  num_nodes = a.num_nodes;
  return *this;
}

template <typename T>
AVLtree<T>::~AVLtree() {
  destroy_nodes(root);
}

template <typename T>
void AVLtree<T>::add_item(T x, Records::record * rec, int fieldnum = 0) {
  root = add_node(root, x, rec, fieldnum);
  num_nodes++;
}

template <typename T>
void AVLtree<T>::search(SearchObject &searchObj)
{
	SStruct * sstruct = searchObj.GetSearchStruct(field_num);
	SearchStruct<T> * searchStruct = dynamic_cast<SearchStruct<T>*>(sstruct);
 	assert(searchStruct != NULL);
	for(int i = 0; i < searchStruct->_searchTermVector.size(); i++)
	{	
		search(root, searchStruct->_searchTermVector[i]->_term,\
				searchObj.GetMutex(), \
				searchStruct->_searchTermVector[i]->_recordNumberVector);
	}
}

template <typename T>
uint AVLtree<T>::size() {
  return num_nodes;
}

template <typename T>
void AVLtree<T>::preorder() {
  preorder(root);
}

template <typename T>
void AVLtree<T>::inorder() {
  inorder(root);
}

template <typename T>
void AVLtree<T>::postorder() {
  postorder(root);
}

template <typename T>
AVLtree<T>::node* AVLtree<T>::copy_nodes(node *n) {
  if (n == NULL) return NULL;
  node* p;
  node* l;
  node* r;
  l = copy_nodes(n->left);
  r = copy_nodes(n->right);
  p = new node(n->item, l, r, n->height);
  return p;
}

template <typename T>
void AVLtree<T>::destroy_nodes(node *n) {
  if (n != NULL) {
    destroy_nodes(n->left);
    destroy_nodes(n->right);
    delete n;
  }
}

template <typename T>
AVLtree<T>::node* AVLtree<T>::add_node(node* n, T x, Records::record * rec = NULL, int fieldnum = 0) {
  if (n == NULL) {
    node* p;
    p = new node(x, NULL, NULL, 1, rec, fieldnum);
    return p;
  } else {
    if (x < n->item) {
      n->left = add_node(n->left, x, rec, fieldnum);
      if (height(n->left) - height(n->right) == 2) {
        if (x < n->left->item) {
          n = rotate_right(n);
        } else {
          n = rotate2_right(n);
        }
      }
    } else {
      n->right = add_node(n->right, x, rec, fieldnum);
      if (height(n->right) - height(n->left) == 2) {
        if (x >= n->right->item) {
          n = rotate_left(n);
        } else {
          n = rotate2_left(n);
        }
      }
    }
    n->height = 1 + maxof(height(n->left), height(n->right));
    return n;
  }
}

template <typename T>
uint AVLtree<T>::maxof(uint a, uint b) {
  if (a > b) return a;
  return b;
}

template <typename T>
uint AVLtree<T>::height(node* n) {
  if (n == NULL) return 0;
  return n->height;
}

template <typename T>
AVLtree<T>::node* AVLtree<T>::rotate_left(node* n) {
  node* p;
  p = n->right;
  n->right = p->left;
  p->left = n;
  n->height = 1 + maxof(height(n->left), height(n->right));
  p->height = 1 + maxof(height(p->left), height(p->right));
  return p;
}

template <typename T>
AVLtree<T>::node* AVLtree<T>::rotate2_left(node* n) {
  n->right = rotate_right(n->right);
  n = rotate_left(n);
  return n;
}

template <typename T>
AVLtree<T>::node* AVLtree<T>::rotate_right(node* n) {
  node* p;
  p = n->left;
  n->left = p->right;
  p->right = n;
  n->height = 1 + maxof(height(n->left), height(n->right));
  p->height = 1 + maxof(height(p->left), height(p->right));
  return p;
}

template <typename T>
AVLtree<T>::node* AVLtree<T>::rotate2_right(node* n) {
  n->left = rotate_left(n->left);
  n = rotate_right(n);
  return n;
}

template <typename T>
void AVLtree<T>::search(node* n, T term, HANDLE mutex, std::vector<int> &recordvector)
{
	if (n != NULL) 
	{
		if(my_type != STRINGTYPE)
		{
			if(n->item >= term)
			{
				search(n->left, term, mutex, recordvector);
			}
		}
		else
		{
			search(n->left, term, mutex, recordvector);
		}

		if(my_type == STRINGTYPE)
		{
			std::string &tempString = reinterpret_cast<std::string&>(n->item);
			if(tempString.find(term) != -1)
			{	
				WaitForSingleObject(mutex,INFINITE);
				recordvector.push_back(n->_rec->getrecordnumber());
				ReleaseMutex(mutex);
			}
		}
		else if (n->item == term)
		{
				WaitForSingleObject(mutex,INFINITE);
				recordvector.push_back(n->_rec->getrecordnumber());
				ReleaseMutex(mutex);
		}
		//end comparison

		if(my_type != STRINGTYPE)
		{
			if(n->item <= term)
			{
				search(n->right, term, mutex, recordvector);
			}
		}
		else
		{
			search(n->right, term, mutex, recordvector);
		}
	}
}

template <typename T>
void AVLtree<T>::preorder(node* n) {
  if (n != NULL) {
    cout << n->item << " ";
    preorder(n->left);
    preorder(n->right);
  }
}

template <typename T>
void AVLtree<T>::inorder(node* n) {
  if (n != NULL) {
    inorder(n->left);
	std::cout << n->item << " ";
    inorder(n->right);
  }
}

template <typename T>
void AVLtree<T>::postorder(node* n) {
  if (n != NULL) {
    postorder(n->left);
    postorder(n->right);
	std::cout << n->item << " ";
  }
}

template <typename T>
bool AVLtree<T>::save(std::ofstream &fout)
{
	if(!fout)
	{
		std::cout << "unable to open for writing";
		return false;
	}

	fout.write((char*) &num_nodes,sizeof num_nodes);

	if (save(root, fout))
	{
		std::cout << "tree saved";
	}
	else
	{//error message handled by inordersave
		fout.close();
		return false;
	}
	fout.close();
	return true;
	
}

template <typename T>
bool AVLtree<T>::save(node * n, std::ofstream & fout)
{
	if (n != NULL) 
	{	
		if (save(n->left, fout))
		{
			fout.write((char*) &n->item, sizeof(n->item));

			if(fout.rdstate())
			{
				std::cout << "write error in tree";
				return false;
			}
		}
		else
		{
			return false;
		}
		if (save(n->right, fout))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}
/*
template <>
bool AVLtree<std::string>::save(node * n, std::ofstream & fout)
{
	if (n != NULL) 
	{	
		if (save(n->left, fout))
		{
			
			const char * temp = n->item.c_str();
			int size = strlen(temp);
			fout.write((char*) &size, sizeof(size));
			fout.write(temp, size);

			if(fout.rdstate())
			{
				std::cout << "write error in tree";
				return false;
			}
		}
		else
		{
			return false;
		}
		if (save(n->right, fout))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return true;
}
*/
template <typename T>
bool AVLtree<T>::read(std::ifstream &fin)
{
	int nnodes;
	fin.read((char*)&nnodes, sizeof(nnodes));
	T ** ptr = new T*[nnodes];
	for(int i = 0; i<nnodes; i++)
	{
		fin.read((char*)ptr[i],sizeof(T));
		add_item(*ptr[i], NULL, 0);
	}
	
	delete [] ptr;
	return true;
}
/*
template <>
bool AVLtree<std::string>::read(std::ifstream &fin)
{
	int size;
	int nnodes;
	
	fin.read((char*)&nnodes, sizeof(nnodes));
	
	char ** ptr = new char*[nnodes];
	
	for(int i = 0; i<nnodes; i++)
	{
		fin.read((char*)&size,sizeof(size));
		ptr[i] = new char[size+1];
		fin.read(ptr[i],size);
		ptr[i][size] = 0;
		add_item(ptr[i], NULL, 0);
	}

	delete [] ptr;

	return true;
}
*/
template <typename T>
void AVLtree<T>::type_me()
{
	const type_info & t = typeid(T);
	
	if(t == typeid(std::string))
	{
		my_type = STRINGTYPE;
		
	}
	else if(t == typeid(int))
	{
		my_type = INTTYPE;
	}
	else if(t == typeid(char))
	{
		my_type = CHARTYPE;
	}
	else if(t == typeid(float))
	{
		my_type = FLOATTYPE;
	}
	else
	{
		//exception here
		std::cout << "unable to recognise type";
	}

}

template <typename T>
AVLtree<T>::node* AVLtree<T>::getparent(T * key)
{
	node *t=getnode(key);
	if(t==NULL || t==root)return NULL;
	node *t1=root;
	while(true)
	{
	if(t1==NULL) return NULL;
	if(t->item > t1->item && &t->item == &t1->right->item)return t1;
	if(t->item < t1->item && &t->item == &t1->left->item)return t1;
	if(t->item > t1->item)  t1 = t1->right;
	else t1 = t1->left;
	}
return NULL;
}

template <typename T>
AVLtree<T>::node* AVLtree<T>::getnode(T * key)
{
	node *t=root;
	while(true)
	{
	    if(t==NULL)return NULL;
	    if(&t->item==key)return t;
	    if(*key>t->item)t=t->right;
	    else t=t->left;
	}
return NULL;
}

template <typename T>
int AVLtree<T>::balance(node *t)
{
	if(t==NULL)return 0;
	return getheight(t->right) - getheight(t->left);
}

template <typename T>
void AVLtree<T>::remove(T * key)
{
	node *t=getnode(key);
	if(t==NULL)return;

	node *q=getparent(key);

	if(t->left!=NULL && t->right!=NULL)
	{
	    /*For replacing with inorder successor*/
	    node *y=getinordersuccessor(t);
	    q=getparent(&y->item);
	    t->item=y->item;
	    t=y;
	}
	node *p=NULL;
	if(q==NULL && t!=root)return;

	int rootchild=(q!=NULL && q==root)?1:0;
	int isroot=(t==root)?1:0;
	int i=(q!=NULL && q->left==t)?0:1;

	if(t->left==NULL && t->right==NULL)
	{
	    if(!isroot)
	    {
		if(!i)q->left=NULL;
		else q->right=NULL;
		delete t;
		p=q;
	    }
	    else
	    {
		root=NULL;
		delete t;
	    }
	}
	else if(t->left==NULL)
	{
	    if(!isroot)
	    {
		if(!i)q->left=t->right;
		else q->right=t->right;
		delete t;
		p=q;
	    }
	    else
	    {
		root=t->right;
		delete t;
	    }
	}
	else if(t->right==NULL)
	{
	    if(!isroot)
	    {
		if(!i)q->left=t->left;
		else q->right=t->left;
		delete t;
		p=q;
	    }
	    else
	    {
		root=t->left;
		delete t;
	    }
	}
	if(rootchild)root=p;
	/*Balancing part*/
	t=p;
	while(t!=NULL)
	{
	    int hd=balance(t);
	    if(fabs(hd)>1)
	    {
		if(hd<0)
		{
		    if(balance(t->left)<0)
		    {
				rotate_right(t);
		    }
		    else
		    {
				rotate2_right(t);
		    }
		}
		else
		{
		    if(balance(t->left)>0)
		    {
				rotate_left(t);
		    }
		    else
		    {
				rotate2_left(t);
		    }
		}
	    }
	    t=getparent(&t->item);
	}
	return;
}

template <typename T>
AVLtree<T>::node* AVLtree<T>::getinordersuccessor(node *t)
{
	t=t->right;
	while(t->left!=NULL)t=t->left;
	return t;
}

template <typename T>
void AVLtree<T>::delete_item(T * x)
{
	remove(x);
}

template <typename T>
int AVLtree<T>::getheight(node *t)
{
	if(t==NULL)return 0;
	int hr=height(t->right);
	int hl=height(t->left);
	return 1+(hr>hl?hr:hl);
}

#endif