/**
 * Mesh.cpp
 *
 *      Date: 2012/05/02
 *      Author: KR
 */

#include "Mesh.h"

#include "Node.h"
#include "Elements/Tri.h"
#include "Elements/Quad.h"
#include "Elements/Tet.h"
#include "Elements/Hex.h"
#include "Elements/Pyramid.h"
#include "Elements/Prism.h"

namespace MeshLib {

Mesh::Mesh(const std::string &name, const std::vector<Node*> &nodes, const std::vector<Element*> &elements)
	: _name(name), _nodes(nodes), _elements(elements)
{
	this->removeIdenticalNodes();
}

Mesh::Mesh(const Mesh &mesh)
	: _name(mesh.getName()), _nodes(mesh.getNodes()), _elements(mesh.getElements())
{
}

Mesh::Mesh(const std::string &file_name)
{
	// read mesh
	this->removeIdenticalNodes();
}

Mesh::~Mesh()
{
	const size_t nElements (_elements.size());
	for (size_t i=0; i<nElements; i++)
		delete _elements[i];

	const size_t nNodes (_nodes.size());
	for (size_t i=0; i<nNodes; i++)
		delete _nodes[i];
}

void Mesh::removeIdenticalNodes()
{
	//check for unique mesh nodes
}

void Mesh::addNode(Node* node)
{
	_nodes.push_back(node); 
}

void Mesh::addElement(Element* elem) 
{
	_elements.push_back(elem); 

	// add element informatin to nodes
	size_t nNodes (elem->getNNodes());
	for (size_t i=0; i<nNodes; i++)
		elem->getNode(i)->addElement(elem);
}
/*
void Mesh::removeNode(size_t idx)
{
	if (idx < _nodes.size())
	{
		const std::vector<const Element*> node_elems = _nodes[idx]->getElements();
		for (std::vector<const Element*>::const_iterator it  = node_elems.begin();
									                     it != node_elems.end(); ++it)
		{
			
			//for (si
		}
		_nodes.erase(_nodes.begin()+idx);
		return;
	}
	std::cerr << "Mesh::removeNode(" << idx << ") - Index does not exist." << std::endl;
}

void Mesh::removeElement(size_t idx)
{
	if (idx < _elements.size())
	{
		Element* elem (_elements[idx]);
		size_t nNodes (elem->getNNodes());
		for (size_t i=0; i<nNodes; i++)
		{
			Node* node (const_cast<Node*>(elem->getNode(i)));
			// remove element from nodes element-list
			if (node->getNElements()>1)	
			{
				std::vector<Node*>::iterator it (_nodes.begin()+node->getID());
				delete node;
				_nodes.erase(it);
			}
			// delete node if it is not part of any element
			else	
				node->removeElement(elem);
		}
		return;
	}
	std::cerr << "Mesh::removeElement(" << idx << ") - Index does not exist." << std::endl;
}
*/
}
