#ifndef CYLINDER_HPP_INCLUDED
#define CYLINDER_HPP_INCLUDED

/**
 * \file     cylinder.hpp
 * \mainpage 3D cylinder sample geometry import
*/

#include <string.h>
#include <vector>

#include "../population/boundary/boundary.hpp"


/**\fn         Cylinder3D
 * \brief      Load pre-defined scenario of a three-dimensional flow around cylinder
 *
 * \tparam     NX               simulation domain resolution in x-direction
 * \tparam     NY               simulation domain resolution in y-direction
 * \tparam     NZ               simulation domain resolution in z-direction
 * \tparam     T                floating data type used for simulation
 * \param[in]  radius           unsigned integer that holds the radius of the cylinder
 * \param[in]  position         array of unsigned integers that holds the position of the center of the
 *                              cylinder
 * \param[in]  orientation      std::string that holds the orientation
 * \param[in]  walls            a boolean variable that indicates if walls on the side should be
 *                              included (true) or not (wrong)
 * \param[out] wall             a pointer to a vector of relevant linear indices that correspond to a wall
 * \param[out] vel_boundary     a pointer to a vector of relevant linear indices that correspond to
 *                              a velocity boundary
 * \param[out] press_boundary   a pointer to a vector of relevant linear indices that correspond to
 *                              a pressure boundary
 * \param[in]  RHO              simulation density
 * \param[in]  U                characteristic velocity (measurement for temporal resolution)
 * \param[in]  L                characteristic length scale of the problem
*/
template <unsigned int NX, unsigned int NY, unsigned int NZ, typename T = double>
void Cylinder3D(unsigned int const radius, std::array<unsigned int,3> const& position,
                std::string const& orientation, bool const walls,
                std::vector<boundaryElement<T>>& wall,
                std::vector<boundaryElement<T>>& inlet, std::vector<boundaryElement<T>>& outlet,
                T const RHO, T const U, T const V, T const W)
{
    if (orientation == "x")
    {
        for(unsigned int z = 0; z < NZ; ++z)
        {
            for(unsigned int y = 0; y < NY; ++y)
            {
                for(unsigned int x = 0; x < NX; ++x)
                {
                    /// create element
                    boundaryElement<T> const element = {x, y, z, RHO, U, V, W};

                    /// add to corresponding boundary
                    if ((x-position[0])*(x-position[0]) + (y-position[1])*(y-position[1]) <= radius*radius)
                    {
                        wall.push_back(element);
                    }
                    else if ((y == 0) || (y == NY-1) || (z == 0) || (z == NZ-1))
                    {
                        if (walls == true)
                        {
                            wall.push_back(element);
                        }
                    }
                    else if (x == 0)
                    {
                        inlet.push_back(element);
                    }
                    else if (x == NX-1)
                    {
                        outlet.push_back(element);
                    }
                }
            }
        }
    }
    else
    {
        std::cerr << "Warning: Geometry orientation " << orientation << " not found." << std::endl;
        exit(EXIT_FAILURE);
    }
}

#endif // CYLINDER_HPP_INCLUDED
