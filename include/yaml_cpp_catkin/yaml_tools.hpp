/**
 * @file yaml_cpp.hpp
 * @author Maximilien Naveau (maximilien.naveau@gmail.com)
 * @license License BSD-3-Clause
 * @copyright Copyright (c) 2019, New York University and Max Planck Gesellschaft.
 * @date 2019-09-30
 */

#pragma once

#include <yaml-cpp/yaml.h>

namespace YAML {

  /**
   * @brief helper function to safely read a yaml parameter
   * 
   * @tparam YamlType 
   * @param node 
   * @param name 
   * @return YamlType 
   */
  template <typename YamlType>
  static YamlType ReadParameter(const YAML::Node& node, const std::string& name) {
    try { return node[name.c_str()].as<YamlType>(); }
    catch (...) { throw std::runtime_error("Error reading the yaml parameter [" + name + "]"); }
  }

  /**
   * @brief helper function to safely read a yaml parameter
   * 
   * @tparam YamlType 
   * @param node 
   * @param name 
   * @param parameter 
   */
  template <typename YamlType>
  static void ReadParameter(const YAML::Node& node, const std::string& name, YamlType& parameter) {
    parameter = ReadParameter<YamlType>(node, name);
  }

}