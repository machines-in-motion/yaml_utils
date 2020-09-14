#include <gtest/gtest.h>

#include "yaml_utils/yaml_cpp_fwd.hpp"

#define PRECISION 1.e-4

class YamlToolsTest: public ::testing::Test {
protected:
	virtual void SetUp() {
	}
	virtual void TearDown() {
	}
};

TEST_F(YamlToolsTest, TestingReadOptionalParameterFunction)
{
	double var_parameter;
	double value_var_parameter1 = 12.;
	double value_var_parameter2 = 24.;
	double value_default = 36.;

	YAML::Node with_var_node, without_var_node;
	with_var_node["var1"] = value_var_parameter1;
	with_var_node["var2"] = value_var_parameter2;

	// Optional and variable exists
	YAML::readParameter(with_var_node, "var1", var_parameter, true);
	EXPECT_NEAR(value_var_parameter1, var_parameter, PRECISION);

	// Mandatory and variable exists
	YAML::readParameter(with_var_node, "var2", var_parameter, false);
	EXPECT_NEAR(value_var_parameter2, var_parameter, PRECISION);

	// Optional and variable does not exists
	var_parameter = 0.0;
	YAML::readParameter(without_var_node, "var1", var_parameter, true);
	EXPECT_NEAR(0.0, var_parameter, PRECISION);

	// Mandatory and variable does not exists
	var_parameter = 0.0;
	try {
		YAML::readParameter(without_var_node, "var2", var_parameter, false);
	} catch (const std::runtime_error& error) {
		std::string e_str = error.what();
		assert(e_str.compare("Error reading the yaml parameter [var2]")==0);
	}

	// Default value: Use provided value if exists.
	YAML::ReadParameterDefault(with_var_node, "var1", var_parameter, value_default);
	EXPECT_NEAR(value_var_parameter1, var_parameter, PRECISION);

	YAML::ReadParameterDefault(with_var_node, "var3", var_parameter, value_default);
	EXPECT_NEAR(value_default, var_parameter, PRECISION);
}
