/**
 * \copyright
 * Copyright (c) 2012-2015, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#include <algorithm>

namespace MeshLib
{

#ifndef WIN32
/// \todo Windows compiler does not accept this definition and issues a linking error.
template <class ELEMENT_RULE>
const unsigned TemplateElement<ELEMENT_RULE>::n_all_nodes;

template <class ELEMENT_RULE>
const unsigned TemplateElement<ELEMENT_RULE>::n_base_nodes;

template <class ELEMENT_RULE>
const unsigned TemplateElement<ELEMENT_RULE>::dimension;
#endif // WIN32

template <class ELEMENT_RULE>
TemplateElement<ELEMENT_RULE>::TemplateElement(Node* nodes[n_all_nodes], unsigned value, std::size_t id)
: Element(value, id)
{
	this->_nodes = nodes;
	this->_neighbors = new Element*[getNNeighbors()];
	std::fill(this->_neighbors, this->_neighbors + getNNeighbors(), nullptr);
	this->_content = ELEMENT_RULE::computeVolume(this->_nodes);
}

template <class ELEMENT_RULE>
TemplateElement<ELEMENT_RULE>::TemplateElement(std::array<Node*, n_all_nodes> const& nodes, unsigned value, std::size_t id)
: Element(value, id)
{
	this->_nodes = new Node*[n_all_nodes];
	std::copy(nodes.begin(), nodes.end(), this->_nodes);
	this->_neighbors = new Element*[getNNeighbors()];
	std::fill(this->_neighbors, this->_neighbors + getNNeighbors(), nullptr);
	this->_content = ELEMENT_RULE::computeVolume(this->_nodes);
}

template <class ELEMENT_RULE>
TemplateElement<ELEMENT_RULE>::TemplateElement(const TemplateElement &e)
: Element(e.getValue(), e.getID())
{
	this->_nodes = new Node*[n_all_nodes];
	for (unsigned i=0; i<n_all_nodes; i++)
		this->_nodes[i] = e._nodes[i];
	this->_neighbors = new Element*[getNNeighbors()];
	for (unsigned i=0; i<getNNeighbors(); i++)
		this->_neighbors[i] = e._neighbors[i];
	this->_content = e.getContent();
}

template <class ELEMENT_RULE>
bool TemplateElement<ELEMENT_RULE>::isEdge(unsigned idx1, unsigned idx2) const
{
	for (unsigned i(0); i<getNEdges(); i++)
	{
		if (ELEMENT_RULE::edge_nodes[i][0]==idx1 && ELEMENT_RULE::edge_nodes[i][1]==idx2) return true;
		if (ELEMENT_RULE::edge_nodes[i][1]==idx1 && ELEMENT_RULE::edge_nodes[i][0]==idx2) return true;
	}
	return false;
}


} // MeshLib

