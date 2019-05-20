/*
 *
 * Copyright [2019] Max Planck Society. All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <iomanip>
#include <Eigen/Eigen>
#include <type_traits>
#include <yaml-cpp/yaml.h>

namespace YAML {

  template < typename _Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
  struct convert< Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols> >
  {
    static Node encode(const Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& matrix)
    {
      Node node(NodeType::Sequence);

      // Save data given as a vector
      if (_Rows == 1 || _Cols == 1) {
        for (unsigned int row=0; row<matrix.rows(); row++)
          for (unsigned int col=0; col<matrix.cols(); col++)
            node.push_back(matrix(row,col));
        return node;
      }

      // Save data given as a matrix
      for (unsigned int row=0; row<matrix.rows(); row++) {
        Node node_row(NodeType::Sequence);
        for (unsigned int col=0; col<matrix.cols(); col++)
          node_row.push_back(matrix(row,col));
        node.push_back(node_row);
      }
      return node;
    }

    static bool decode(const Node& node, Eigen::Matrix<_Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>& matrix)
    {
      // Read data given as a vector
      if (_Rows == 1 || _Cols == 1) {
        (_Rows == 1 ? matrix.resize(_Rows, node.size()) : matrix.resize(node.size(), _Cols));
        for (unsigned int id=0; id<node.size(); id++)
          (node[0].size() == 0 ? matrix(id) = node[(int)id].as<_Scalar>() :  matrix(id) = node[(int)id][0].as<_Scalar>());
        return true;
      }

      // Read data given as a matrix
      if (_Rows == Eigen::Dynamic || _Cols == Eigen::Dynamic)
        matrix.resize(node.size(), node[0].size());
      for (unsigned int row=0; row<node.size(); row++) {
        for (unsigned int col=0; col<node[0].size(); col++)
          matrix(row,col) = node[(int)row][(int)col].as<_Scalar>();
      }
      return true;
    }
  };

} // namespace YAML
