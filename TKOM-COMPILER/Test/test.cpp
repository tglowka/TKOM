#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE TKOM_COMPILER_TESTS
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test.hpp>
#include <boost/test/output_test_stream.hpp>
#include "../parser.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string getFileContent(){
    ifstream ifs("output.txt");
    std::string content( (std::istreambuf_iterator<char>(ifs) ),
                      (std::istreambuf_iterator<char>()    ) );
    return content;
}
BOOST_AUTO_TEST_SUITE( list_value_tests )
    BOOST_AUTO_TEST_CASE( test_number_list_value )
    {
         vector<double>* myList = ParserStructure::parseListDefinitionNumber("{1.5,2.1,3.0}");
         vector<double>* destList = new vector<double>();
         destList->push_back(1.5);
         destList->push_back(2.1);
         destList->push_back(3.0);
         BOOST_TEST( *myList == *destList);
    }

    BOOST_AUTO_TEST_CASE( test_string_list_value )
    {
         vector<string>* myList = ParserStructure::parseListDefinitionString("{\'jeden\',\'dwa\',\'trzy\'}");
         vector<string>* destList = new vector<string>();
         destList->push_back("jeden");
         destList->push_back("dwa");
         destList->push_back("trzy");
         BOOST_TEST( *myList == *destList);
    }
BOOST_AUTO_TEST_SUITE_END();

BOOST_AUTO_TEST_SUITE( abstract_syntex_tree_tests )
/*
==============================================================================
----------------------------Number Variable-----------------------------------
==============================================================================
*/
    BOOST_AUTO_TEST_CASE( test_definition_num_var )
    {
         system("../lexer \"begin\" \"var number aa=2\" \"end\"");
         BOOST_TEST( getFileContent().c_str() == "begin\nvar number aa=2\nend\n");
    }

    BOOST_AUTO_TEST_CASE( test_declaration_num_var )
    {
         system("../lexer \"begin\" \"var number aa\" \"end\"");
         BOOST_TEST( getFileContent().c_str() == "begin\nvar number aa\nend\n");
    }

    BOOST_AUTO_TEST_CASE( test_initialization_num_var )
    {
         system("../lexer \"begin\" \"aa=55\" \"end\"");
         BOOST_TEST( getFileContent().c_str() == "begin\naa=55\nend\n");
    }

/*
==============================================================================
----------------------------List Number Variable -----------------------------
==============================================================================
*/
    BOOST_AUTO_TEST_CASE( test_definition_num_list )
    {
         system("../lexer \"begin\" \"number aa={1.5,2.0,3.7}\" \"end\"");
         BOOST_TEST( getFileContent().c_str() == "begin\nnumber aa=1.5 2 3.7 \nend\n");
    }

    BOOST_AUTO_TEST_CASE( test_declaration_num_list )
    {
         system("../lexer \"begin\" \"number aa\" \"end\"");
         BOOST_TEST( getFileContent().c_str() == "begin\nnumber aa\nend\n");
    }

    BOOST_AUTO_TEST_CASE( test_initialization_num_list )
    {
         system("../lexer \"begin\" \"aa={1.5,2.0,3.7}\" \"end\"");
         BOOST_TEST( getFileContent().c_str() == "begin\naa=1.5 2 3.7 \nend\n");
    }
/*
==============================================================================
----------------------------List String Variable -----------------------------
==============================================================================
*/
BOOST_AUTO_TEST_CASE( test_definition_string_list )
{
     system("../lexer \"begin\" \"string aa={\'test1\',\'test2\'}\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nstring aa=\"test1\" \"test2\" \nend\n");
}

BOOST_AUTO_TEST_CASE( test_declaration_string_list )
{
     system("../lexer \"begin\" \"string aa\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nstring aa\nend\n");
}

BOOST_AUTO_TEST_CASE( test_initialization_string_list )
{
     system("../lexer \"begin\" \"aa={\'test1\',\'test2\'}\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\naa=\"test1\" \"test2\" \nend\n");
}
/*
==============================================================================
----------------------------Variable assign ----------------------------------
==============================================================================
*/
BOOST_AUTO_TEST_CASE( test_var_assign_string_list )
{
     system("../lexer \"begin\" \"string aa=bb\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nstring aa=bb\nend\n");
}

BOOST_AUTO_TEST_CASE( test_var_assign_num_list )
{
     system("../lexer \"begin\" \"number aa=bb\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nnumber aa=bb\nend\n");
}

BOOST_AUTO_TEST_CASE( test_var_assign_num_var )
{
     system("../lexer \"begin\" \"var number aa=bb\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nvar number aa=bb\nend\n");
}

BOOST_AUTO_TEST_CASE( test_var_assign_var )
{
     system("../lexer \"begin\" \"aa=bb\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\naa=bb\nend\n");
}
/*
==============================================================================
----------------------------Arithmetic operators------------------------------
==============================================================================
*/
BOOST_AUTO_TEST_CASE( test_scalar_plus_operator_definition )
{
     system("../lexer \"begin\" \"var number aa = 10 + 15\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nvar number aa=(10+15)\nend\n");
}

BOOST_AUTO_TEST_CASE( test_scalar_minut_operator_definition )
{
     system("../lexer \"begin\" \"var number aa = 10 - 15\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nvar number aa=(10-15)\nend\n");
}

BOOST_AUTO_TEST_CASE( test_scalar_mul_operator_definition )
{
     system("../lexer \"begin\" \"var number aa = 10 * 15\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nvar number aa=(10*15)\nend\n");
}

BOOST_AUTO_TEST_CASE( test_scalar_div_operator_definition )
{
     system("../lexer \"begin\" \"var number aa = 10 / 15\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nvar number aa=(10/15)\nend\n");
}

BOOST_AUTO_TEST_CASE( test_scalar_plus_operator_initialization )
{
     system("../lexer \"begin\" \"aa = 10 + 15\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\naa=(10+15)\nend\n");
}

BOOST_AUTO_TEST_CASE( test_scalar_minus_operator_initialization )
{
     system("../lexer \"begin\" \"aa = 10 - 15\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\naa=(10-15)\nend\n");
}

BOOST_AUTO_TEST_CASE( test_scalar_mul_operator_initialization )
{
     system("../lexer \"begin\" \"aa = 10 * 15\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\naa=(10*15)\nend\n");
}

BOOST_AUTO_TEST_CASE( test_scalar_div_operator_initialization )
{
     system("../lexer \"begin\" \"aa = 10 / 15\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\naa=(10/15)\nend\n");
}

BOOST_AUTO_TEST_CASE( test_scalar_precedence )
{
     system("../lexer \"begin\" \"aa = 10 / 15 + 10 * 10\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\naa=((10/15)+(10*10))\nend\n");
}

BOOST_AUTO_TEST_CASE( test_scalar_precedence_brackets )
{
     system("../lexer \"begin\" \"aa = 10 / (15 + 10) * 10\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\naa=((10/(15+10))*10)\nend\n");
}
/*
==============================================================================
----------------------------Relational operators---------------------------------
==============================================================================
*/
BOOST_AUTO_TEST_CASE( test_relational_precedence_less )
{
     system("../lexer \"begin\" \"if aa > bb then\" \"aa = ww\" \"end if\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nif (aa>bb)then\naa=ww\nend if\nend\n");
}

BOOST_AUTO_TEST_CASE( test_relational_precedence_greater )
{
     system("../lexer \"begin\" \"if aa < bb then\" \"aa = ww\" \"end if\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nif (aa<bb)then\naa=ww\nend if\nend\n");
}

BOOST_AUTO_TEST_CASE( test_relational_precedence_equal )
{
     system("../lexer \"begin\" \"if aa == bb then\" \"aa = ww\" \"end if\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nif (aa==bb)then\naa=ww\nend if\nend\n");
}

BOOST_AUTO_TEST_CASE( test_relational_precedence_nequal )
{
     system("../lexer \"begin\" \"if aa >= bb then\" \"aa = ww\" \"end if\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nif (aa>=bb)then\naa=ww\nend if\nend\n");
}

BOOST_AUTO_TEST_CASE( test_relational_precedence_lequal )
{
     system("../lexer \"begin\" \"if aa <= bb then\" \"aa = ww\" \"end if\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nif (aa<=bb)then\naa=ww\nend if\nend\n");
}

BOOST_AUTO_TEST_CASE( test_relational_precedence_gequal )
{
     system("../lexer \"begin\" \"if aa != bb then\" \"aa = ww\" \"end if\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nif (aa!=bb)then\naa=ww\nend if\nend\n");
}
/*
==============================================================================
----------------------------If statement-------------------------------------
==============================================================================
*/
BOOST_AUTO_TEST_CASE( test_if_statement )
{
     system("../lexer \"begin\" \"if aa > bb or bb < dd and cc == ee then\" \"aa = ww\" \"end if\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nif ((aa>bb) OR ((bb<dd) AND (cc==ee)))then\naa=ww\nend if\nend\n");
}

/*
==============================================================================
----------------------------Foreach statement---------------------------------
==============================================================================
*/
BOOST_AUTO_TEST_CASE( test_foreach_statement )
{
     system("../lexer \"begin\" \"foreach x in MyList loop\" \"x = 10\" \"end loop\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nforeach x in MyList loop\nx=10\nend loop\nend\n");
}

/*
==============================================================================
----------------------------Show statement------------------------------------
==============================================================================
*/
BOOST_AUTO_TEST_CASE( test_show_statement )
{
     system("../lexer \"begin\" \"show(ab)\"     \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nshow (ab)\nend\n");
}

/*
==============================================================================
----------------------------List filter expression----------------------------
==============================================================================
*/
BOOST_AUTO_TEST_CASE( test_filter_expression )
{
     system("../lexer \"begin\" \"MyList = MyList[>100]\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nMyList=MyList[>100]\nend\n");
}

/*
==============================================================================
----------------------------Sub List expression-------------------------------
==============================================================================
*/
BOOST_AUTO_TEST_CASE( test_sublist_expression )
{
     system("../lexer \"begin\" \"MyList = MyList[2,5]\" \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nMyList=MyList[2,5]\nend\n");
}

/*
==============================================================================
----------------------------Function execution--------------------------------
==============================================================================
*/
BOOST_AUTO_TEST_CASE( test_function )
{
     system("../lexer \"begin\" \"function number fun1( arg var number n4 arg number n5 arg string n6 )\"  \"begin\"  \"n1=10\" \"n2={1,2,3}\" \"n3={\'sd\'}\"  \"end function\"   \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\nfunction number fun1( arg varnumber n4 arg number n5 arg string n6 )\nbegin\nn1=10\nn2=1 2 3 \nn3=\"sd\" \nend\n\nend\n");
}

/*
==============================================================================
----------------------------Commenta------------------------------------------
==============================================================================
*/
BOOST_AUTO_TEST_CASE( test_comments )
{
     system("../lexer \"begin\" \"#jakisrandomowycoment\"   \"end\"");
     BOOST_TEST( getFileContent().c_str() == "begin\n#jakisrandomowycoment\n\nend\n");
}

BOOST_AUTO_TEST_SUITE_END();
