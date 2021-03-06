/**
 * @copyright
 * Copyright (c) 2012-2015, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/LICENSE.txt
 */
#ifndef BOUNDARYELEMENTSSEARCHER_H_
#define BOUNDARYELEMENTSSEARCHER_H_

#include <vector>

namespace GeoLib
{
class GeoObject;
class Polyline;
class Surface;
}

namespace MeshLib
{
class Mesh;
class Element;
}

namespace MeshGeoToolsLib
{
class MeshNodeSearcher;
class BoundaryElementsAlongPolyline;
class BoundaryElementsOnSurface;

/**
 * This class searches boundary elements located on a given geometric object, i.e. polyline and surface.
 * Note that internal boundaries are currently not supported.
 */
class BoundaryElementsSearcher
{
public:
	/**
	 * Constructor
	 * @param mesh             a mesh object
	 * @param mshNodeSearcher  a MeshNodeSearcher object which is internally used to search mesh nodes
	 */
	BoundaryElementsSearcher(MeshLib::Mesh const& mesh, MeshNodeSearcher &mshNodeSearcher);

	/// destructor
	virtual ~BoundaryElementsSearcher();

	/**
	 * generate boundary elements on the given geometric object (point, polyline, surface).
	 *
	 * @param geoObj a GeoLib::GeoObject where the nearest mesh node is searched for
	 * @return a vector of boundary element objects
	 */
	std::vector<MeshLib::Element*> const& getBoundaryElements(GeoLib::GeoObject const& geoObj);

	/**
	 * generate boundary elements on the given polyline.
	 * @param ply the GeoLib::Polyline the nearest mesh nodes are searched for
	 * @return a vector of boundary element objects
	 */
	std::vector<MeshLib::Element*> const& getBoundaryElementsAlongPolyline(GeoLib::Polyline const& ply);

	/**
	 * generate boundary elements on the given surface.
	 * @param sfc the GeoLib::Surface the nearest mesh nodes are searched for
	 * @return a vector of boundary element objects
	 */
	std::vector<MeshLib::Element*> const& getBoundaryElementsOnSurface(GeoLib::Surface const& sfc);


private:
	MeshLib::Mesh const& _mesh;
	MeshNodeSearcher &_mshNodeSearcher;
	std::vector<BoundaryElementsAlongPolyline*> _boundary_elements_along_polylines;
	std::vector<BoundaryElementsOnSurface*> _boundary_elements_along_surfaces;
};

} // end namespace MeshGeoTools

#endif /* BOUNDARYELEMENTSSEARCHER_H_ */
