#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "iron.h"

#pragma region "Unit Test Case for Vector2 class"
#pragma region "Unit Test Case 1 - Default contructor of the Vector2 object"
SCENARIO("Default contructor of the Vector2 object.", "[Vector2]") {
	GIVEN("An uninitialized Vector2 object.") {
		iron::Vector2 v;

		REQUIRE(v.x == NULL);
		REQUIRE(v.y == NULL);

		WHEN("The object is initialized with the default contructor.") {
			v = iron::Vector2();

			THEN("The x and y must be equal to 0.0f and 0.0f.") {
				REQUIRE(v.x == 0.0f);
				REQUIRE(v.y == 0.0f);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 2 - Coordinates contructor of the Vector2 object"
SCENARIO("Coordinates contructor of the Vector2 object.", "[Vector2]") {
	GIVEN("An uninitialized Vector2 object.") {
		iron::Vector2 v;

		REQUIRE(v.x == NULL);
		REQUIRE(v.y == NULL);

		WHEN("The object is initialized with int values.") {
			v = iron::Vector2((int)1, (int)1);

			THEN("The x and y are converted to floats of the same value.") {
				REQUIRE(v.x == 1.0f);
				REQUIRE(v.y == 1.0f);
			}
		}

		WHEN("The object is initialized with float values.") {
			v = iron::Vector2(2.0f, 2.0f);

			THEN("The x and y must be equal to 2.0f.") {
				REQUIRE(v.x == 2.0f);
				REQUIRE(v.y == 2.0f);
			}
		}

		WHEN("The object is initialized with double values.") {
			v = iron::Vector2((double)3, (double)3);

			THEN("The x and y are converted to floats of the same value.") {
				REQUIRE(v.x == 3.0f);
				REQUIRE(v.y == 3.0f);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 3 - Contructor based on the direction of 2 other Vector2 objects"
SCENARIO("Contructor based on the direction of 2 other Vector2 objects.", "[Vector2]") {
	GIVEN("2 initialized Vector2 objects and 1 uninitialized Vector2 object.") {
		iron::Vector2 v;
		iron::Vector2 v1 = iron::Vector2(1, 1);
		iron::Vector2 v2 = iron::Vector2(2, 2);

		REQUIRE(v.x == NULL);
		REQUIRE(v.y == NULL);
		REQUIRE(v1.x == 1.0f);
		REQUIRE(v1.y == 1.0f);
		REQUIRE(v2.x == 2.0f);
		REQUIRE(v2.y == 2.0f);

		WHEN("The object \"v\" is constructed with the direction of \"v1\" and \"v2\".") {
			v = iron::Vector2(v1, v2);

			THEN("The x and y must be equal to 1.0f and 1.0f.") {
				REQUIRE(v.x == 1.0f);
				REQUIRE(v.y == 1.0f);
			}
		}

		WHEN("The object \"v\" is constructed with the direction of 2 zeroed vectors.") {
			v1 = iron::Vector2();
			v2 = iron::Vector2();
			v = iron::Vector2(v1, v2);

			THEN("The x and y must be equal to 0.0f and 0.0f.") {
				REQUIRE(v.x == 0.0f);
				REQUIRE(v.y == 0.0f);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 4 - Static Methods of the Vector2 object to check certain coordinate values"
SCENARIO("Static Methods of the Vector2 object to check certain coordinate values.", "[Vector2]") {
	GIVEN("An uninitialized Vector2 object.") {
		iron::Vector2 v;
		REQUIRE(v.x == NULL);
		REQUIRE(v.y == NULL);

		WHEN("The object is initialized with the static method zero().") {
			v = iron::Vector2::zero();

			THEN("The x and y must be equal to 0.0f.") {
				REQUIRE(v.x == 0.0f);
				REQUIRE(v.y == 0.0f);
			}
		}

		WHEN("The object is initialized with the static method pOne().") {
			v = iron::Vector2::pOne();

			THEN("The x and y must be equal to 1.0f.") {
				REQUIRE(v.x == 1.0f);
				REQUIRE(v.y == 1.0f);
			}
		}

		WHEN("The object is initialized with the static method nOne().") {
			v = iron::Vector2::nOne();

			THEN("The x and y must be equal to -1.0f.") {
				REQUIRE(v.x == -1.0f);
				REQUIRE(v.y == -1.0f);
			}
		}

		WHEN("The object is initialized with the static method pX().") {
			v = iron::Vector2::pX();

			THEN("The x and y must be equal to 1.0f and 0.0f.") {
				REQUIRE(v.x == 1.0f);
				REQUIRE(v.y == 0.0f);
			}
		}

		WHEN("The object is initialized with the static method nX().") {
			v = iron::Vector2::nX();

			THEN("The x and y must be equal to -1.0f and 0.0f.") {
				REQUIRE(v.x == -1.0f);
				REQUIRE(v.y == 0.0f);
			}
		}

		WHEN("The object is initialized with the static method pY().") {
			v = iron::Vector2::pY();

			THEN("The x and y must be equal to 0.0f and 1.0f.") {
				REQUIRE(v.x == 0.0f);
				REQUIRE(v.y == 1.0f);
			}
		}

		WHEN("The object is initialized with the static method nY().") {
			v = iron::Vector2::nY();

			THEN("The x and y must be equal to 0.0f and -1.0f.") {
				REQUIRE(v.x == 0.0f);
				REQUIRE(v.y == -1.0f);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 5 - "Is" Methods of the Vector2 object"
SCENARIO("\"Is\" Methods of the Vector2 object.", "[Vector2]") {
	GIVEN("3 initialized Vector2 objects, \"v1\" set to 0s, \"v2\" set to 1s. and \"v3\" set to -1s.") {
		iron::Vector2 v1(0.0f, 0.0f);
		iron::Vector2 v2(1.0f, 1.0f);
		iron::Vector2 v3(-1.0f, -1.0f);

		REQUIRE(v1.x == 0.0f);
		REQUIRE(v1.y == 0.0f);
		REQUIRE(v2.x == 1.0f);
		REQUIRE(v2.y == 1.0f);
		REQUIRE(v3.x == -1.0f);
		REQUIRE(v3.y == -1.0f);

		WHEN("The method isZero() is called for the objects") {
			THEN("\"v1s\" method must return true, \"v2\" and \"v3s\" method must return false") {
				REQUIRE(v1.isZero() == true);
				REQUIRE(v2.isZero() == false);
				REQUIRE(v3.isZero() == false);
			}
		}

		WHEN("The method isOne() is called for the objects") {
			THEN("\"v2s\" method must return true, \"v1\" and \"v3s\" method must return false") {
				REQUIRE(v1.isOne() == false);
				REQUIRE(v2.isOne() == true);
				REQUIRE(v3.isOne() == false);
			}
		}

		WHEN("The method isNOne() is called for the objects") {
			THEN("\"v3s\" method must return true, \"v1\" and \"v2s\" method must return false") {
				REQUIRE(v1.isNOne() == false);
				REQUIRE(v2.isNOne() == false);
				REQUIRE(v3.isNOne() == true);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 6 - Negating of the Vector2 object"
SCENARIO("Negating of the Vector2 object.", "[Vector2]") {
	GIVEN("2 initialized Vector2 objects, \"v1\" set to 3 and -4 and \"v2\" set to -2 and 2.") {
		iron::Vector2 v1(3.0f, -4.0f);
		iron::Vector2 v2(-2.0f, 2.0f);

		REQUIRE(v1.x == 3.0f);
		REQUIRE(v1.y == -4.0f);
		REQUIRE(v2.x == -2.0f);
		REQUIRE(v2.y == 2.0f);

		WHEN("The method negate() is called for the objects") {
			v1.negate();
			v2.negate();

			THEN("\"v1\" coordinates must be -3 and -4 and \"v2\" coordinates must be -2 and 2.") {
				REQUIRE(v1.x == -3.0f);
				REQUIRE(v1.y == 4.0f);
				REQUIRE(v2.x == 2.0f);
				REQUIRE(v2.y == -2.0f);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 7 - Addition operations of the Vector2 object"
SCENARIO("Addition operations of the Vector2 object.", "[Vector2]") {
	GIVEN("2 initialized Vector2 objects, \"v1\" set to 1 and \"v2\" set to -5 and 0.") {
		iron::Vector2 v1(2.0f, 2.0f);
		iron::Vector2 v2(-5.0f, 0.0f);

		REQUIRE(v1.x == 2.0f);
		REQUIRE(v1.y == 2.0f);
		REQUIRE(v2.x == -5.0f);
		REQUIRE(v2.y == 0.0f);

		WHEN("The method add(int, int) is called for the objects \"v1\" and \"v2\".") {
			v1.add(2, 4);
			v2.add(-2, 0);

			THEN("\"v1\" and \"v2\" will add the parameters to their respective coordinates.") {
				REQUIRE(v1.x == 4.0f);
				REQUIRE(v1.y == 6.0f);
				REQUIRE(v2.x == -7.0f);
				REQUIRE(v2.y == 0.0f);
			}
		}

		WHEN("The method add(float, float) is called for the objects \"v1\" and \"v2\".") {
			v1.add(-1.0f, -1.5f);
			v2.add(2.9f, 100.123456f);

			THEN("\"v1\" and \"v2\" will add the parameters to their respective coordinates.") {
				REQUIRE(v1.x == 1.0f);
				REQUIRE(v1.y == 0.5f);
				REQUIRE(v2.x == -2.1f);
				REQUIRE(v2.y == 100.123456f);
			}
		}

		WHEN("The method add(double, double) is called for the objects \"v1\" and \"v2\".") {
			v1.add(1123.5f, -150.87f);
			v2.add(-2.56847f, 206100.156f);

			THEN("\"v1\" and \"v2\" will add the parameters to their respective coordinates.") {
				REQUIRE(v1.x == 1125.5f);
				REQUIRE(v1.y == -148.87f);
				REQUIRE(v2.x == -7.56847f);
				REQUIRE(v2.y == 206100.156f);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 8 - Addition operations with 2 Vector2 objects"
SCENARIO("Addition operations with 2 Vector2 objects.", "[Vector2]") {
	GIVEN("2 initialized Vector2 objects, \"v1\" set to 1 and -1 and \"v2\" set to 5 and 3.") {
		iron::Vector2 v1(1.0f, -1.0f);
		iron::Vector2 v2(5.0f, 3.0f);

		REQUIRE(v1.x == 1.0f);
		REQUIRE(v1.y == -1.0f);
		REQUIRE(v2.x == 5.0f);
		REQUIRE(v2.y == 3.0f);

		WHEN("The method add(Vector2) is called for the object \"v1\" passing \"v2\" as the parameter.") {
			v1.add(v2);

			THEN("\"v1\" contains the sum between \"v1\" and \"v2\".") {
				REQUIRE(v1.x == 6.0f);
				REQUIRE(v1.y == 2.0f);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 9 - Addition operations with 2 Vector2 objects and a pointer to store the result"
SCENARIO("Addition operations with 2 Vector2 objects and a pointer to store the result.", "[Vector2]") {
	GIVEN("2 initialized Vector2 objects, \"v1\" set to 5 and -5, \"v2\" set to 1 and 2 and a pointer to a Vector2 object that stores the result") {
		iron::Vector2 v1(5.1f, -5.0f);
		iron::Vector2 v2(1.0f, 2.5f);
		iron::Vector2 *v = new iron::Vector2();

		REQUIRE(v1.x == 5.1f);
		REQUIRE(v1.y == -5.0f);
		REQUIRE(v2.x == 1.0f);
		REQUIRE(v2.y == 2.5f);
		REQUIRE(v);

		WHEN("The method add(Vector2, Vector2, Vector2*) with the parameters \"v1\", \"v2\" and \"v\" respectively.") {
			iron::Vector2::add(v1, v2, v);

			THEN("\"v\" contains the sum between \"v1\" and \"v2\".") {
				REQUIRE(v->x == 6.1f);
				REQUIRE(v->y == -2.5f);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 10 - Subtraction operations of the Vector2 object"
SCENARIO("Subtraction operations of the Vector2 object.", "[Vector2]") {
	GIVEN("2 initialized Vector2 objects, \"v1\" set to 7 and -5 and \"v2\" set to -2 and 1.") {
		iron::Vector2 v1(7.0f, -5.0f);
		iron::Vector2 v2(-2.0f, 1.0f);

		REQUIRE(v1.x == 7.0f);
		REQUIRE(v1.y == -5.0f);
		REQUIRE(v2.x == -2.0f);
		REQUIRE(v2.y == 1.0f);

		WHEN("The method subtract(int, int) is called for the objects \"v1\" and \"v2\".") {
			v1.subtract(6, -1);
			v2.subtract(-12.21f, 15.021f);

			THEN("\"v1\" and \"v2\" will subtract the parameters to their respective coordinates.") {
				REQUIRE(v1.x == 1);
				REQUIRE(v1.y == -4);
				REQUIRE(v2.x == 10.21f);
				REQUIRE(v2.y == -14.021f);
			}
		}

		WHEN("The method subtract(float, float) is called for the objects \"v1\" and \"v2\".") {
			v1.subtract(-1.5f, 3.65f);
			v2.subtract(15.5f, -12.34f);

			THEN("\"v1\" and \"v2\" will subtract the parameters to their respective coordinates.") {
				REQUIRE(v1.x == 8.5f);
				REQUIRE(v1.y == -8.65f);
				REQUIRE(v2.x == -17.5f);
				REQUIRE(v2.y == 13.34f);
			}
		}

		WHEN("The method subtract(double, double) is called for the objects \"v1\" and \"v2\".") {
			v1.subtract(-156.01f, 0.0f);
			v2.subtract(-1.0f, 2.5f);

			THEN("\"v1\" and \"v2\" will subtract the parameters to their respective coordinates.") {
				REQUIRE(v1.x == 163.01f);
				REQUIRE(v1.y == -5);
				REQUIRE(v2.x == -1);
				REQUIRE(v2.y == -1.5f);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 11 - Subtraction operations with 2 Vector2 objects"
SCENARIO("Subtraction operations with 2 Vector2 objects.", "[Vector2]") {
	GIVEN("2 initialized Vector2 objects, \"v1\" set to -1 and 0.0 and \"v2\" set to 2 and 2.15.") {
		iron::Vector2 v1(-1.0f, 0.0f);
		iron::Vector2 v2(2.0f, 2.15f);

		REQUIRE(v1.x == -1.0f);
		REQUIRE(v1.y == 0.0f);
		REQUIRE(v2.x == 2.0f);
		REQUIRE(v2.y == 2.15f);

		WHEN("The method subtract(Vector2) is called for the object \"v1\" passing \"v2\" as the parameter.") {
			v1.subtract(v2);

			THEN("\"v1\" contains the difference between \"v2\" and \"v1\".") {
				REQUIRE(v1.x == -3.0f);
				REQUIRE(v1.y == -2.15f);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 12 - Subtraction operations with 2 Vector2 objects and a pointer to store the result"
SCENARIO("Subtraction operations with 2 Vector2 objects and a pointer to store the result.", "[Vector2]") {
	GIVEN("2 initialized Vector2 objects, \"v1\" set to 8 and 2, \"v2\" set to -1.2 and 0 and a pointer to a Vector2 object that stores the result") {
		iron::Vector2 v1(8.0f, 2.0f);
		iron::Vector2 v2(-1.2f, 0.0f);
		iron::Vector2 *v = new iron::Vector2();

		REQUIRE(v1.x == 8.0f);
		REQUIRE(v1.y == 2.0f);
		REQUIRE(v2.x == -1.2f);
		REQUIRE(v2.y == 0.0f);
		REQUIRE(v);

		WHEN("The method subtract(Vector2, Vector2, Vector2*) with the parameters \"v1\", \"v2\" and \"v\" respectively.") {
			iron::Vector2::subtract(v1, v2, v);

			THEN("\"v\" contains the difference between \"v2\" and \"v1\".") {
				REQUIRE(v->x == 9.2f);
				REQUIRE(v->y == 2.0f);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 13 - Scaling operations of the Vector2 object"
SCENARIO("Scaling operations of the Vector2 object.", "[Vector2]") {
	GIVEN("2 initialized Vector2 objects, \"v1\" set to 2 and 2.5 and \"v2\" set to 1.5 and -2.") {
		iron::Vector2 v1(2.0f, 2.5f);
		iron::Vector2 v2(1.5f, -2.0f);

		REQUIRE(v1.x == 2.0f);
		REQUIRE(v1.y == 2.5f);
		REQUIRE(v2.x == 1.5f);
		REQUIRE(v2.y == -2.0f);

		WHEN("The method scale(int, int) is called for the objects \"v1\" and \"v2\".") {
			v1.scale(2);
			v2.scale(-1.5f);

			THEN("\"v1\" and \"v2\" will scale the coordinates with the given parameters.") {
				REQUIRE(v1.x == 4);
				REQUIRE(v1.y == 5);
				REQUIRE(v2.x == -2.25f);
				REQUIRE(v2.y == 3);
			}
		}

		WHEN("The method scale(float, float) is called for the objects \"v1\" and \"v2\".") {
			v1.scale(1.25);
			v2.scale(-50.2f);

			THEN("\"v1\" and \"v2\" will scale the coordinates with the given parameters.") {
				REQUIRE(v1.x == 2.5f);
				REQUIRE(v1.y == 3.125f);
				REQUIRE(v2.x == -75.3f);
				REQUIRE(v2.y == 100.4f);
			}
		}

		WHEN("The method scale(double, double) is called for the objects \"v1\" and \"v2\".") {
			v1.scale(500);
			v2.scale(1000);

			THEN("\"v1\" and \"v2\" will scale the coordinates with the given parameters.") {
				REQUIRE(v1.x == 1000.0f);
				REQUIRE(v1.y == 1250.0f);
				REQUIRE(v2.x == 1500.0f);
				REQUIRE(v2.y == -2000.0f);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 14 - Dividing operations of the Vector2 object"
SCENARIO("Dividing operations of the Vector2 object.", "[Vector2]") {
	GIVEN("2 initialized Vector2 objects, \"v1\" set to 10 and 5 and \"v2\" set to -5 and 2.") {
		iron::Vector2 v1(10.0f, 5.0f);
		iron::Vector2 v2(-5.0f, 2.0f);

		REQUIRE(v1.x == 10.0f);
		REQUIRE(v1.y == 5.0f);
		REQUIRE(v2.x == -5.0f);
		REQUIRE(v2.y == 2.0f);

		WHEN("The method divide(int) is called for the objects \"v1\" and \"v2\".") {
			v1.divide(5);
			v2.divide(0.2f);

			THEN("\"v1\" and \"v2\" will divide the coordinates with the given parameters.") {
				REQUIRE(v1.x == 2);
				REQUIRE(v1.y == 1);
				REQUIRE(v2.x == -25);
				REQUIRE(v2.y == 10);
			}
		}

		WHEN("The method divide(float) is called for the objects \"v1\" and \"v2\".") {
			v1.divide(-2.5f);
			v2.divide(0.1f);

			THEN("\"v1\" and \"v2\" will divide the coordinates with the given parameters.") {
				REQUIRE(v1.x == -4);
				REQUIRE(v1.y == -2);
				REQUIRE(v2.x == -50);
				REQUIRE(v2.y == 20);
			}
		}

		WHEN("The method divide(double) is called for the objects \"v1\" and \"v2\".") {
			v1.divide(1);
			v2.divide(-5.0f);

			THEN("\"v1\" and \"v2\" will divide the coordinates with the given parameters.") {
				REQUIRE(v1.x == 10.0f);
				REQUIRE(v1.y == 5.0f);
				REQUIRE(v2.x == 1);
				REQUIRE(v2.y == -0.4f);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 15 - Setter operations of the Vector2 object"
SCENARIO("Setter operations of the Vector2 object.", "[Vector2]") {
	GIVEN("1 initialized Vector2 object set to 0.") {
		iron::Vector2 v;

		REQUIRE(v.x == 0.0f);
		REQUIRE(v.y == 0.0f);

		WHEN("The method set(int, int) is called for the object \"v\".") {
			v.set(2, 4);

			THEN("\"v\" must have 2 and 4 as coordinates.") {
				REQUIRE(v.x == 2);
				REQUIRE(v.y == 4);
			}
		}

		WHEN("The method set(float, float) is called for the object \"v\".") {
			v.set(-4, 5161);

			THEN("\"v\" must have -4 and 5161 as coordinates.") {
				REQUIRE(v.x == -4);
				REQUIRE(v.y == 5161);
			}
		}

		WHEN("The method set(double, double) is called for the object \"v\".") {
			v.set(5.0, -498.5);

			THEN("\"v\" must have 5.0 and -498.5 as coordinates.") {
				REQUIRE(v.x == 5.0);
				REQUIRE(v.y == -498.5);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 16 - Setter operations with 2 vectors as parameters of the Vector2 object"
SCENARIO("Setter operations with 2 vectors as parameters of the Vector2 object.", "[Vector2]") {
	GIVEN("1 initialized Vector2 object set to 0. 2 initialized Vector2 objects (p1 and p2) set to 2 and 4 respectively.") {
		iron::Vector2 v;
		iron::Vector2 p1(2, 2);
		iron::Vector2 p2(4, 4);

		REQUIRE(v.x == 0.0f);
		REQUIRE(v.y == 0.0f);
		REQUIRE(p1.x == 2.0f);
		REQUIRE(p1.y == 2.0f);
		REQUIRE(p2.x == 4.0f);
		REQUIRE(p2.y == 4.0f);

		WHEN("The method set(Vector2, Vector2) is called for the object \"v\" with the arguments \"p1\" and \"p2\".") {
			v.set(p1, p2);

			THEN("\"v\" must have the difference between \"p2\" and \"p1\", 2.") {
				REQUIRE(v.x == 2);
				REQUIRE(v.y == 2);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 17 - Setter operations with 1 vector as parameter of the Vector2 object"
SCENARIO("Setter operations with 1 vector as parameter of the Vector2 object.", "[Vector2]") {
	GIVEN("1 initialized Vector2 object set to 0. initialized Vector2 objects set to 1 and 2.") {
		iron::Vector2 v;
		iron::Vector2 p1(1, 2);

		REQUIRE(v.x == 0.0f);
		REQUIRE(v.y == 0.0f);
		REQUIRE(p1.x == 1.0f);
		REQUIRE(p1.y == 2.0f);

		WHEN("The method set(Vector2) is called for the object \"v\" with the arguments \"p1\".") {
			v.set(p1);

			THEN("\"v\" copies the values of \"p1\".") {
				REQUIRE(v.x == 1);
				REQUIRE(v.y == 2);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 18 - Overloaded operators of the Vector2 object"
SCENARIO("Overloaded operators of the Vector2 object.", "[Vector2]") {
	GIVEN("3 initialized Vector2 object set to 1, 2 and -1 respectively.") {
		iron::Vector2 v1(1, 1);
		iron::Vector2 v2(2, 2);
		iron::Vector2 v3(-1, -1);

		REQUIRE(v1.x == 1.0f);
		REQUIRE(v1.y == 1.0f);
		REQUIRE(v2.x == 2.0f);
		REQUIRE(v2.y == 2.0f);
		REQUIRE(v3.x == -1.0f);
		REQUIRE(v3.y == -1.0f);

		WHEN("The operator = is used to assign \"v2\" to \"v1\".") {
			v1 = v2;

			THEN("\"v1\" must have the values of \"v2\".") {
				REQUIRE(v1.x == 2);
				REQUIRE(v1.y == 2);
			}
		}

		WHEN("The operator == is used to determine if \"v1\" is equal to \"v3\".") {
			bool result = (v1 == v3);

			THEN("The return must be false.") {
				REQUIRE_FALSE(result);
			}
		}

		WHEN("The operator != is used to determine if \"v2\" is equal to \"v3\".") {
			bool result = (v2 != v3);

			THEN("The return must be true.") {
				REQUIRE(result);
			}
		}

		WHEN("The operator < is used to determine if \"v2\" is below \"v3\".") {
			bool result = (v2 < v3);

			THEN("The return must be false.") {
				REQUIRE_FALSE(result);
			}
		}

		WHEN("The operator <= is used to determine if \"v3\" is below \"v1\".") {
			bool result = (v3 <= v1);

			THEN("The return must be true.") {
				REQUIRE(result);
			}
		}

		WHEN("The operator > is used to determine if \"v2\" is above \"v3\".") {
			bool result = (v2 > v3);

			THEN("The return must be true.") {
				REQUIRE(result);
			}
		}

		WHEN("The operator >= is used to determine if \"v3\" is above \"v1\".") {
			bool result = (v3 >= v1);

			THEN("The return must be false.") {
				REQUIRE_FALSE(result);
			}
		}

		WHEN("The operator + is used to determine the sum between \"v1\" and \"v2\".") {
			iron::Vector2 result = v1 + v2;

			THEN("The variable \"result\" must hold the result of the sum.") {
				REQUIRE(result.x == 3);
				REQUIRE(result.y == 3);
			}
		}

		WHEN("The operator += is used to determine the sum between \"v1\" and \"v2\" and store it in \"v1\".") {
			v1 += v2;

			THEN("The variable \"v1\" must hold the result of the sum.") {
				REQUIRE(v1.x == 3);
				REQUIRE(v1.y == 3);
			}
		}

		WHEN("The operator - is used to determine the subtraction between \"v1\" and \"v2\".") {
			iron::Vector2 result = v1 - v2;

			THEN("The variable \"result\" must hold the result of the subtraction.") {
				REQUIRE(result.x == -1);
				REQUIRE(result.y == -1);
			}
		}

		WHEN("The operator -= is used to determine the subtraction between \"v1\" and \"v2\" and store it in \"v1\".") {
			v1 -= v2;

			THEN("The variable \"v1\" must hold the result of the subtraction.") {
				REQUIRE(v1.x == -1);
				REQUIRE(v1.y == -1);
			}
		}

		WHEN("The operator - is used to negate a Vector2 object, in this case, \"v3\".") {
			THEN("The negation of \"v3\" must yield the negation of both the x and y variables.") {
				REQUIRE(-v3.x == 1);
				REQUIRE(-v3.y == 1);
			}
		}

		WHEN("The operator * is used to scale the vector \"v2\" by a given scalar.") {
			iron::Vector2 result = v2 * -2;

			THEN("The variable \"result\" must hold the result of the scaling.") {
				REQUIRE(result.x == -4);
				REQUIRE(result.y == -4);
			}
		}

		WHEN("The operator *= is used to scale the vector \"v2\" by a given scalar and store it in \"v2\".") {
			v2 *= -2;

			THEN("The variable \"v2\" must hold the result of the scaling.") {
				REQUIRE(v2.x == -4);
				REQUIRE(v2.y == -4);
			}
		}

		WHEN("The operator / is used to divide the vector \"v2\" by a given denominator.") {
			iron::Vector2 result = v2 / 2;

			THEN("The variable \"result\" must hold the result of the dividing.") {
				REQUIRE(result.x == 1);
				REQUIRE(result.y == 1);
			}
		}

		WHEN("The operator /= is used to divide the vector \"v2\" by a given denominator and store it in \"v2\".") {
			v2 /= 2;

			THEN("The variable \"v2\" must hold the result of the dividing.") {
				REQUIRE(v2.x == 1);
				REQUIRE(v2.y == 1);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 19 - Clamp feature of the Vector2 object"
SCENARIO("Clamp feature of the Vector2 object.", "[Vector2]") {
	GIVEN("5 initialized Vector2 objects with the following values: (400, 2.95) : (-5153.1, 56) : (400, 2.95) : (400, 2.95) : (400, 2.95). 1 pointer to a Vector2 object to store results.") {
		iron::Vector2 v1(400.0f, 2.95f);
		iron::Vector2 v2(-5153.1f, 56.0f);
		iron::Vector2 v3(0.5f, 0.5f);
		iron::Vector2 v4(-4.0f, -7.0f);
		iron::Vector2 v5(57.4f, 53.1f);
		iron::Vector2* ptr = new iron::Vector2();

		WHEN("The method clamp(Vector2, float, float, float, float, Vector2*) is called with the following parameters: (v1, 0, 10, 500, 20, ptr).") {
			iron::Vector2::clamp(v1, 0, 10, 500, 20, ptr);

			THEN("\"ptr\" values will be set to 400 and 10.") {
				REQUIRE(ptr->x == 400);
				REQUIRE(ptr->y == 10);
			}
		}

		WHEN("The method clamp(Vector2, float, float, float, float, Vector2*) is called with the following parameters: (v2, 5, 5, 6, 50, ptr).") {
			iron::Vector2::clamp(v2, 5, 5, 6, 50, ptr);

			THEN("\"ptr\" values will be set to 5 and 50.") {
				REQUIRE(ptr->x == 5);
				REQUIRE(ptr->y == 50);
			}
		}

		WHEN("The method clamp(Vector2, Vector2, Vector2, Vector2*) is called with the following parameters: (v2, Vector2(0, 0), Vector2(1, 1), ptr).") {
			iron::Vector2::clamp(v3, iron::Vector2(0, 0), iron::Vector2(1, 1), ptr);

			THEN("\"ptr\" values will be set to 0.5 and 0.5.") {
				REQUIRE(ptr->x == 0.5f);
				REQUIRE(ptr->y == 0.5f);
			}
		}

		WHEN("The method clamp(float, float, float, float) is called with the following parameters: (-5, -6, -7.5, -7.5).") {
			v4.clamp(-7.5f, -7.5f, -5.0f, -6.0f);

			THEN("\"v4\" values will be set to 0.5 and 0.5.") {
				REQUIRE(v4.x == -5.0f);
				REQUIRE(v4.y == -7.0f);
			}
		}

		WHEN("The method clamp(Vector2, Vector2) is called with the following parameters: (Vector2(57.2, 53.2), Vector2(57.3, 53.3)).") {
			v5.clamp(iron::Vector2(57.2f, 53.2f), iron::Vector2(57.3f, 53.3f));

			THEN("\"v5\" values will be set to 57.3 and 53.2.") {
				REQUIRE(v5.x == 57.3f);
				REQUIRE(v5.y == 53.2f);
			}
		}
	}
}
#pragma endregion;

#pragma region "Unit Test Case 20 - Rotation operations of the Vector2 Object"
SCENARIO("Rotation operations of the Vector2 Object.", "[Vector2]") {
	GIVEN("3 initialized Vector2 objects with the following values: (0, 10) : (x, y) : (0, 0).") {
		iron::Vector2 v1(0.0f, 10.0f);
		iron::Vector2 v2(2.0f, -1.0f);
		iron::Vector2 pivot(0.0f, 0.0f);

		WHEN("The method rotate(float, float, float) is called with the following parameters: (0, 0, PI/2).") {
			v1.rotate(0, 0, iron::IronMath::MATH_PIOVER2);

			THEN("\"v1\" values will be set to 10 and 0.") {
				REQUIRE(v1.x == -10);
				REQUIRE(roundf(v1.y) == 0);
			}
		}

		WHEN("The method rotate(Vector2&, float) is called with the following parameters: (Vector2(1, 1), PI).") {
			v2.rotate(iron::Vector2(1.0f, 1.0f), iron::IronMath::MATH_PI);

			THEN("\"v1\" values will be set to 0 and 3.") {
				REQUIRE(roundf(v2.x) == 0);
				REQUIRE(roundf(v2.y) == 3);
			}
		}
	}
}
#pragma endregion;
#pragma endregion;

#pragma region "Unit Test Case for IronMath class"
#pragma region "Unit Test Case 1 - Degrees and radians conversion"
SCENARIO("Degrees and radians conversion.", "[IronMath]") {
	GIVEN("The values 90 (degrees) and pi (radians)") {
		WHEN("The static method deg_to_rad(float) is called with 90 as parameter.") {
			float rad = iron::IronMath::deg_to_rad(90);

			THEN("The result must be equal to half pi.") {
				REQUIRE(rad == iron::IronMath::MATH_PIOVER2);
			}
		}

		WHEN("The static method rad_to_deg(float) is called with pi as parameter.") {
			float deg = iron::IronMath::rad_to_deg(iron::IronMath::MATH_PI);

			THEN("The result must be equal to 180.") {
				REQUIRE(deg == 180);
			}
		}
	}
}
#pragma endregion;
#pragma endregion;