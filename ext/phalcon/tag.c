
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_operators.h>
#include <Zend/zend_exceptions.h>
#include <Zend/zend_interfaces.h>

#include "kernel/main.h"
#include "kernel/array.h"
#include "kernel/memory.h"
#include "kernel/object.h"
#include "kernel/operators.h"
#include "kernel/fcall.h"
#include "kernel/hash.h"
#include "kernel/concat.h"
#include "kernel/exception.h"
#include "kernel/string.h"


/*
 +------------------------------------------------------------------------+
 | Phalcon Framework                                                      |
 +------------------------------------------------------------------------+
 | Copyright (c) 2011-2014 Phalcon Team (http://www.phalconphp.com)       |
 +------------------------------------------------------------------------+
 | This source file is subject to the New BSD License that is bundled     |
 | with this package in the file docs/LICENSE.txt.                        |
 |                                                                        |
 | If you did not receive a copy of the license and are unable to         |
 | obtain it through the world-wide-web, please send an email             |
 | to license@phalconphp.com so we can send you a copy immediately.       |
 +------------------------------------------------------------------------+
 | Authors: Andres Gutierrez <andres@phalconphp.com>                      |
 |          Eduar Carvajal <eduar@phalconphp.com>                         |
 |          Nikolaos Dimopoulos <nikos@phalconphp.com>                    |
 +------------------------------------------------------------------------+
 */
/**
 * Phalcon\Tag
 *
 * Phalcon\Tag is designed to simplify building of HTML tags.
 * It provides a set of helpers to generate HTML in a dynamic way.
 * This component is an abstract class that you can extend to add more helpers.
 */
ZEPHIR_INIT_CLASS(Phalcon_Tag) {

	ZEPHIR_REGISTER_CLASS(Phalcon, Tag, phalcon, tag, phalcon_tag_method_entry, 0);

	/**
	 * Pre-asigned values for components
	 */
	zend_declare_property_null(phalcon_tag_ce, SL("_displayValues"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	/**
	 * HTML document title
	 */
	zend_declare_property_null(phalcon_tag_ce, SL("_documentTitle"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(phalcon_tag_ce, SL("_documentTitleSeparator"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_long(phalcon_tag_ce, SL("_documentType"), 11, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	/**
	 * Framework Dispatcher
	 */
	zend_declare_property_null(phalcon_tag_ce, SL("_dependencyInjector"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(phalcon_tag_ce, SL("_urlService"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(phalcon_tag_ce, SL("_dispatcherService"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_null(phalcon_tag_ce, SL("_escaperService"), ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_property_bool(phalcon_tag_ce, SL("_autoEscape"), 1, ZEND_ACC_PROTECTED|ZEND_ACC_STATIC TSRMLS_CC);

	zend_declare_class_constant_long(phalcon_tag_ce, SL("HTML32"), 1 TSRMLS_CC);

	zend_declare_class_constant_long(phalcon_tag_ce, SL("HTML401_STRICT"), 2 TSRMLS_CC);

	zend_declare_class_constant_long(phalcon_tag_ce, SL("HTML401_TRANSITIONAL"), 3 TSRMLS_CC);

	zend_declare_class_constant_long(phalcon_tag_ce, SL("HTML401_FRAMESET"), 4 TSRMLS_CC);

	zend_declare_class_constant_long(phalcon_tag_ce, SL("HTML5"), 5 TSRMLS_CC);

	zend_declare_class_constant_long(phalcon_tag_ce, SL("XHTML10_STRICT"), 6 TSRMLS_CC);

	zend_declare_class_constant_long(phalcon_tag_ce, SL("XHTML10_TRANSITIONAL"), 7 TSRMLS_CC);

	zend_declare_class_constant_long(phalcon_tag_ce, SL("XHTML10_FRAMESET"), 8 TSRMLS_CC);

	zend_declare_class_constant_long(phalcon_tag_ce, SL("XHTML11"), 9 TSRMLS_CC);

	zend_declare_class_constant_long(phalcon_tag_ce, SL("XHTML20"), 10 TSRMLS_CC);

	zend_declare_class_constant_long(phalcon_tag_ce, SL("XHTML5"), 11 TSRMLS_CC);

	return SUCCESS;

}

PHP_METHOD(Phalcon_Tag, getEscaper) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *params, *result = NULL, *autoescape = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &params);



	ZEPHIR_OBS_VAR(autoescape);
	if (!(zephir_array_isset_string_fetch(&autoescape, params, SS("escape"), 0 TSRMLS_CC))) {
		ZEPHIR_OBS_NVAR(autoescape);
		zephir_read_static_property_ce(&autoescape, phalcon_tag_ce, SL("_autoEscape") TSRMLS_CC);
	}
	if (zephir_is_true(autoescape)) {
		ZEPHIR_CALL_SELF(&result, "getescaperservice", NULL);
		zephir_check_call_status();
	} else {
		ZEPHIR_INIT_NVAR(result);
		ZVAL_NULL(result);
	}
	RETURN_CCTOR(result);

}

PHP_METHOD(Phalcon_Tag, renderAttributes) {

	zephir_nts_static zephir_fcall_cache_entry *_5 = NULL;
	HashTable *_2, *_7;
	HashPosition _1, _6;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *code_param = NULL, *attributes, *order, *escaper = NULL, *attrs = NULL, *value = NULL, *escaped = NULL, *attribute = NULL, *key = NULL, *_0, **_3, *_4 = NULL, **_8, *_9 = NULL;
	zval *code = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &code_param, &attributes);

	zephir_get_strval(code, code_param);
	ZEPHIR_SEPARATE_PARAM(code);


	ZEPHIR_INIT_VAR(attrs);
	array_init(attrs);
	ZEPHIR_INIT_VAR(order);
	array_init_size(order, 12);
	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "type", 1);
	zephir_array_fast_append(order, _0);
	ZEPHIR_INIT_BNVAR(_0);
	ZVAL_STRING(_0, "for", 1);
	zephir_array_fast_append(order, _0);
	ZEPHIR_INIT_BNVAR(_0);
	ZVAL_STRING(_0, "src", 1);
	zephir_array_fast_append(order, _0);
	ZEPHIR_INIT_BNVAR(_0);
	ZVAL_STRING(_0, "href", 1);
	zephir_array_fast_append(order, _0);
	ZEPHIR_INIT_BNVAR(_0);
	ZVAL_STRING(_0, "action", 1);
	zephir_array_fast_append(order, _0);
	ZEPHIR_INIT_BNVAR(_0);
	ZVAL_STRING(_0, "id", 1);
	zephir_array_fast_append(order, _0);
	ZEPHIR_INIT_BNVAR(_0);
	ZVAL_STRING(_0, "name", 1);
	zephir_array_fast_append(order, _0);
	ZEPHIR_INIT_BNVAR(_0);
	ZVAL_STRING(_0, "value", 1);
	zephir_array_fast_append(order, _0);
	ZEPHIR_INIT_BNVAR(_0);
	ZVAL_STRING(_0, "class", 1);
	zephir_array_fast_append(order, _0);
	ZEPHIR_CALL_SELF(&escaper, "getescaper", NULL, attributes);
	zephir_check_call_status();
	zephir_is_iterable(attributes, &_2, &_1, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(attribute, _2, _1);
		ZEPHIR_GET_HVALUE(value, _3);
		if (zephir_array_isset(order, attribute)) {
			zephir_array_update_zval(&attrs, attribute, &value, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_CALL_FUNCTION(&_4, "array_merge_recursive", &_5, attrs, attributes);
	zephir_check_call_status();
	ZEPHIR_CPY_WRT(attrs, _4);
	zephir_array_unset_string(&attrs, SS("escape"), PH_SEPARATE);
	zephir_is_iterable(attrs, &_7, &_6, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_7, (void**) &_8, &_6) == SUCCESS
	  ; zephir_hash_move_forward_ex(_7, &_6)
	) {
		ZEPHIR_GET_HMKEY(key, _7, _6);
		ZEPHIR_GET_HVALUE(value, _8);
		if (Z_TYPE_P(key) == IS_STRING) {
			if (zephir_is_true(escaper)) {
				ZEPHIR_CALL_METHOD(&escaped, escaper, "escapehtmlattr", NULL, value);
				zephir_check_call_status();
			} else {
				ZEPHIR_CPY_WRT(escaped, value);
			}
			ZEPHIR_INIT_LNVAR(_9);
			ZEPHIR_CONCAT_SVSVS(_9, " ", key, "=\"", escaped, "\"");
			zephir_concat_self(&code, _9 TSRMLS_CC);
		}
	}
	RETURN_CTOR(code);

}

/**
 * Sets the dependency injector container.
 *
 * @param Phalcon\DiInterface dependencyInjector
 */
PHP_METHOD(Phalcon_Tag, setDI) {

	zval *dependencyInjector;

	zephir_fetch_params(0, 1, 0, &dependencyInjector);



	if (!(zephir_instance_of_ev(dependencyInjector, phalcon_diinterface_ce TSRMLS_CC))) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(spl_ce_InvalidArgumentException, "Parameter 'dependencyInjector' must be an instance of 'Phalcon\\DiInterface'", "", 0);
		return;
	}
	if (Z_TYPE_P(dependencyInjector) != IS_OBJECT) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(phalcon_tag_exception_ce, "Parameter dependencyInjector must be an Object", "phalcon/tag.zep", 140);
		return;
	}
	zephir_update_static_property_ce(phalcon_tag_ce, SL("_dependencyInjector"), dependencyInjector TSRMLS_CC);

}

/**
 * Internally gets the request dispatcher
 *
 * @return Phalcon\DiInterface
 */
PHP_METHOD(Phalcon_Tag, getDI) {

	zval *_0;


	_0 = zephir_fetch_static_property_ce(phalcon_tag_ce, SL("_dependencyInjector") TSRMLS_CC);
	RETURN_CTORW(_0);

}

/**
 * Return a URL service from the default DI
 *
 * @return Phalcon\Mvc\UrlInterface
 */
PHP_METHOD(Phalcon_Tag, getUrlService) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *url = NULL, *dependencyInjector = NULL, *_1 = NULL, *_2;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(url);
	zephir_read_static_property_ce(&url, phalcon_tag_ce, SL("_urlService") TSRMLS_CC);
	if (Z_TYPE_P(url) != IS_OBJECT) {
		ZEPHIR_OBS_VAR(dependencyInjector);
		zephir_read_static_property_ce(&dependencyInjector, phalcon_tag_ce, SL("_dependencyInjector") TSRMLS_CC);
		if (Z_TYPE_P(dependencyInjector) != IS_OBJECT) {
			ZEPHIR_CALL_CE_STATIC(&dependencyInjector, phalcon_di_ce, "getdefault", &_0);
			zephir_check_call_status();
		}
		if (Z_TYPE_P(dependencyInjector) != IS_OBJECT) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_tag_exception_ce, "A dependency injector container is required to obtain the \"url\" service", "phalcon/tag.zep", 174);
			return;
		}
		ZEPHIR_INIT_VAR(_2);
		ZVAL_STRING(_2, "url", 0);
		ZEPHIR_CALL_METHOD(&_1, dependencyInjector, "getshared", NULL, _2);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(url, _1);
		zephir_update_static_property_ce(phalcon_tag_ce, SL("_urlService"), url TSRMLS_CC);
	}
	RETURN_CCTOR(url);

}

/**
 * Returns an Escaper service from the default DI
 *
 * @return Phalcon\EscaperInterface
 */
PHP_METHOD(Phalcon_Tag, getEscaperService) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *escaper = NULL, *dependencyInjector = NULL, *_1 = NULL, *_2;

	ZEPHIR_MM_GROW();

	ZEPHIR_OBS_VAR(escaper);
	zephir_read_static_property_ce(&escaper, phalcon_tag_ce, SL("_escaperService") TSRMLS_CC);
	if (Z_TYPE_P(escaper) != IS_OBJECT) {
		ZEPHIR_OBS_VAR(dependencyInjector);
		zephir_read_static_property_ce(&dependencyInjector, phalcon_tag_ce, SL("_dependencyInjector") TSRMLS_CC);
		if (Z_TYPE_P(dependencyInjector) != IS_OBJECT) {
			ZEPHIR_CALL_CE_STATIC(&dependencyInjector, phalcon_di_ce, "getdefault", &_0);
			zephir_check_call_status();
		}
		if (Z_TYPE_P(dependencyInjector) != IS_OBJECT) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_tag_exception_ce, "A dependency injector container is required to obtain the \"escaper\" service", "phalcon/tag.zep", 202);
			return;
		}
		ZEPHIR_INIT_VAR(_2);
		ZVAL_STRING(_2, "escaper", 0);
		ZEPHIR_CALL_METHOD(&_1, dependencyInjector, "getshared", NULL, _2);
		zephir_check_temp_parameter(_2);
		zephir_check_call_status();
		ZEPHIR_CPY_WRT(escaper, _1);
		zephir_update_static_property_ce(phalcon_tag_ce, SL("_escaperService"), escaper TSRMLS_CC);
	}
	RETURN_CCTOR(escaper);

}

/**
 * Set autoescape mode in generated html
 *
 * @param boolean autoescape
 */
PHP_METHOD(Phalcon_Tag, setAutoescape) {

	zval *autoescape_param = NULL, *_0;
	zend_bool autoescape;

	zephir_fetch_params(0, 1, 0, &autoescape_param);

	autoescape = zephir_get_boolval(autoescape_param);


	ZEPHIR_INIT_ZVAL_NREF(_0);
	ZVAL_BOOL(_0, autoescape);
	zephir_update_static_property_ce(phalcon_tag_ce, SL("_autoEscape"), _0 TSRMLS_CC);

}

/**
 * Assigns default values to generated tags by helpers
 *
 * <code>
 * //Assigning "peter" to "name" component
 * Phalcon\Tag::setDefault("name", "peter");
 *
 * //Later in the view
 * echo Phalcon\Tag::textField("name"); //Will have the value "peter" by default
 * </code>
 *
 * @param string id
 * @param string value
 */
PHP_METHOD(Phalcon_Tag, setDefault) {

	zend_bool _0;
	zval *id_param = NULL, *value;
	zval *id = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &id_param, &value);

	zephir_get_strval(id, id_param);


	if (Z_TYPE_P(value) != IS_NULL) {
		_0 = Z_TYPE_P(value) == IS_ARRAY;
		if (!(_0)) {
			_0 = Z_TYPE_P(value) == IS_OBJECT;
		}
		if (_0) {
			ZEPHIR_THROW_EXCEPTION_DEBUG_STR(phalcon_tag_exception_ce, "Only scalar values can be assigned to UI components", "phalcon/tag.zep", 239);
			return;
		}
	}
	zephir_update_static_property_array_multi_ce(phalcon_tag_ce, SL("_displayValues"), &value TSRMLS_CC, SL("z"), 1, id);
	ZEPHIR_MM_RESTORE();

}

/**
 * Assigns default values to generated tags by helpers
 *
 * <code>
 * //Assigning "peter" to "name" component
 * Phalcon\Tag::setDefaults(array("name" => "peter"));
 *
 * //Later in the view
 * echo Phalcon\Tag::textField("name"); //Will have the value "peter" by default
 * </code>
 *
 * @param array values
 */
PHP_METHOD(Phalcon_Tag, setDefaults) {

	zval *values;

	zephir_fetch_params(0, 1, 0, &values);



	if (Z_TYPE_P(values) != IS_ARRAY) {
		ZEPHIR_THROW_EXCEPTION_DEBUG_STRW(phalcon_tag_exception_ce, "An array is required as default values", "phalcon/tag.zep", 261);
		return;
	}
	zephir_update_static_property_ce(phalcon_tag_ce, SL("_displayValues"), values TSRMLS_CC);

}

/**
 * Alias of Phalcon\Tag::setDefault
 *
 * @param string id
 * @param string value
 */
PHP_METHOD(Phalcon_Tag, displayTo) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *id, *value;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &id, &value);



	ZEPHIR_RETURN_CALL_SELF("setdefault", NULL, id, value);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Check if a helper has a default value set using Phalcon\Tag::setDefault or value from _POST
 *
 * @param string name
 * @return boolean
 */
PHP_METHOD(Phalcon_Tag, hasValue) {

	zval *name, *_0, *_POST;

	zephir_fetch_params(0, 1, 0, &name);



	_0 = zephir_fetch_static_property_ce(phalcon_tag_ce, SL("_displayValues") TSRMLS_CC);
	if (zephir_array_isset(_0, name)) {
		RETURN_BOOL(1);
	} else {
		zephir_get_global(&_POST, SS("_POST") TSRMLS_CC);
		if (zephir_array_isset(_POST, name)) {
			RETURN_BOOL(1);
		}
	}
	RETURN_BOOL(0);

}

/**
 * Every helper calls this function to check whether a component has a predefined
 * value using Phalcon\Tag::setDefault or value from _POST
 *
 * @param string name
 * @param array params
 * @return mixed
 */
PHP_METHOD(Phalcon_Tag, getValue) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *name, *params = NULL, *value = NULL, *autoescape, *_0, *_POST, *_1, *_2 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &name, &params);

	if (!params) {
		params = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_OBS_VAR(value);
	_0 = zephir_fetch_static_property_ce(phalcon_tag_ce, SL("_displayValues") TSRMLS_CC);
	if (!(zephir_array_isset_fetch(&value, _0, name, 0 TSRMLS_CC))) {
		ZEPHIR_OBS_NVAR(value);
		zephir_get_global(&_POST, SS("_POST") TSRMLS_CC);
		if (!(zephir_array_isset_fetch(&value, _POST, name, 0 TSRMLS_CC))) {
			RETURN_MM_NULL();
		}
	}
	if (Z_TYPE_P(value) == IS_STRING) {
		_1 = zephir_fetch_static_property_ce(phalcon_tag_ce, SL("_autoEscape") TSRMLS_CC);
		if (zephir_is_true(_1)) {
			ZEPHIR_CALL_SELF(&_2, "getescaperservice", NULL);
			zephir_check_call_status();
			ZEPHIR_RETURN_CALL_METHOD(_2, "escapehtmlattr", NULL, value);
			zephir_check_call_status();
			RETURN_MM();
		}
		if (Z_TYPE_P(params) == IS_ARRAY) {
			ZEPHIR_OBS_VAR(autoescape);
			if (zephir_array_isset_string_fetch(&autoescape, params, SS("escape"), 0 TSRMLS_CC)) {
				if (zephir_is_true(autoescape)) {
					ZEPHIR_CALL_SELF(&_2, "getescaperservice", NULL);
					zephir_check_call_status();
					ZEPHIR_RETURN_CALL_METHOD(_2, "escapehtmlattr", NULL, value);
					zephir_check_call_status();
					RETURN_MM();
				}
			}
		}
	}
	RETURN_CCTOR(value);

}

/**
 * Resets the request and internal values to avoid those fields will have any default value
 */
PHP_METHOD(Phalcon_Tag, resetInput) {

	HashTable *_2;
	HashPosition _1;
	zval *key = NULL, *value = NULL, *_0, *_POST, **_3;

	ZEPHIR_MM_GROW();

	ZEPHIR_INIT_VAR(_0);
	array_init(_0);
	zephir_update_static_property_ce(phalcon_tag_ce, SL("_displayValues"), _0 TSRMLS_CC);
	zephir_get_global(&_POST, SS("_POST") TSRMLS_CC);
	zephir_is_iterable(_POST, &_2, &_1, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(key, _2, _1);
		ZEPHIR_GET_HVALUE(value, _3);
		zephir_array_unset(&_POST, key, PH_SEPARATE);
	}
	ZEPHIR_MM_RESTORE();

}

/**
 * Builds a HTML A tag using framework conventions
 *
 *<code>
 *	echo Phalcon\Tag::linkTo("signup/register", "Register Here!");
 *	echo Phalcon\Tag::linkTo(array("signup/register", "Register Here!"));
 *	echo Phalcon\Tag::linkTo(array("signup/register", "Register Here!", "class" => "btn-primary"));
 *	echo Phalcon\Tag::linkTo("http://phalconphp.com/", "Phalcon", FALSE);
 *	echo Phalcon\Tag::linkTo(array("http://phalconphp.com/", "Phalcon Home", FALSE));
 *	echo Phalcon\Tag::linkTo(array("http://phalconphp.com/", "Phalcon Home", "local" =>FALSE));
 *</code>
 *
 * @param array|string parameters
 * @param string text
 * @param boolean local
 * @return string
 */
PHP_METHOD(Phalcon_Tag, linkTo) {

	HashTable *_2;
	HashPosition _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *text = NULL, *local = NULL, *key = NULL, *value = NULL, *params = NULL, *action = NULL, *url = NULL, *code, *_0 = NULL, **_3, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &parameters, &text, &local);

	if (!text) {
		ZEPHIR_CPY_WRT(text, ZEPHIR_GLOBAL(global_null));
	} else {
		ZEPHIR_SEPARATE_PARAM(text);
	}
	if (!local) {
		ZEPHIR_CPY_WRT(local, ZEPHIR_GLOBAL(global_true));
	} else {
		ZEPHIR_SEPARATE_PARAM(local);
	}


	if (Z_TYPE_P(parameters) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(params);
		array_init_size(params, 4);
		zephir_array_fast_append(params, parameters);
		zephir_array_fast_append(params, text);
		zephir_array_fast_append(params, local);
	} else {
		ZEPHIR_CPY_WRT(params, parameters);
	}
	ZEPHIR_OBS_VAR(action);
	if (!(zephir_array_isset_long_fetch(&action, params, 0, 0 TSRMLS_CC))) {
		ZEPHIR_OBS_NVAR(action);
		if (!(zephir_array_isset_string_fetch(&action, params, SS("action"), 0 TSRMLS_CC))) {
			ZEPHIR_INIT_BNVAR(action);
			ZVAL_STRING(action, "", 1);
		} else {
			zephir_array_unset_string(&params, SS("action"), PH_SEPARATE);
		}
	}
	ZEPHIR_OBS_NVAR(text);
	if (!(zephir_array_isset_long_fetch(&text, params, 1, 0 TSRMLS_CC))) {
		ZEPHIR_OBS_NVAR(text);
		if (!(zephir_array_isset_string_fetch(&text, params, SS("text"), 0 TSRMLS_CC))) {
			ZEPHIR_INIT_BNVAR(text);
			ZVAL_STRING(text, "", 1);
		} else {
			zephir_array_unset_string(&params, SS("text"), PH_SEPARATE);
		}
	}
	ZEPHIR_OBS_NVAR(local);
	if (!(zephir_array_isset_long_fetch(&local, params, 2, 0 TSRMLS_CC))) {
		ZEPHIR_OBS_NVAR(local);
		if (!(zephir_array_isset_string_fetch(&local, params, SS("local"), 0 TSRMLS_CC))) {
			ZEPHIR_INIT_BNVAR(local);
			ZVAL_BOOL(local, 1);
		} else {
			zephir_array_unset_string(&params, SS("local"), PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_VAR(code);
	if (zephir_is_true(local)) {
		ZEPHIR_CALL_SELF(&url, "geturlservice", NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&_0, url, "get", NULL, action);
		zephir_check_call_status();
		ZEPHIR_CONCAT_SVS(code, "<a href=\"", _0, "\"");
	} else {
		ZEPHIR_CONCAT_SVS(code, "<a href=\"", action, "\"");
	}
	zephir_is_iterable(params, &_2, &_1, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(key, _2, _1);
		ZEPHIR_GET_HVALUE(value, _3);
		if (Z_TYPE_P(key) != IS_LONG) {
			ZEPHIR_INIT_LNVAR(_4);
			ZEPHIR_CONCAT_SVSVS(_4, " ", key, "=\"", value, "\"");
			zephir_concat_self(&code, _4 TSRMLS_CC);
		}
	}
	ZEPHIR_INIT_LNVAR(_4);
	ZEPHIR_CONCAT_SVS(_4, ">", text, "</a>");
	zephir_concat_self(&code, _4 TSRMLS_CC);
	RETURN_CCTOR(code);

}

/**
 * Builds generic INPUT tags
 *
 * @param   string type
 * @param	array parameters
 * @param 	boolean asValue
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, _inputField) {

	HashTable *_4;
	HashPosition _3;
	int ZEPHIR_LAST_CALL_STATUS;
	zend_bool asValue;
	zval *type_param = NULL, *parameters, *asValue_param = NULL, *params = NULL, *id, *value = NULL, *key = NULL, *code = NULL, *name, *_0, *_1 = NULL, **_5, *_6 = NULL, *_7;
	zval *type = NULL, *_2;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 1, &type_param, &parameters, &asValue_param);

	zephir_get_strval(type, type_param);
	if (!asValue_param) {
		asValue = 0;
	} else {
		asValue = zephir_get_boolval(asValue_param);
	}


	ZEPHIR_INIT_VAR(params);
	array_init(params);
	if (Z_TYPE_P(parameters) != IS_ARRAY) {
		zephir_array_append(&params, parameters, PH_SEPARATE);
	} else {
		ZEPHIR_CPY_WRT(params, parameters);
	}
	if (asValue == 0) {
		ZEPHIR_OBS_VAR(id);
		if (!(zephir_array_isset_long_fetch(&id, params, 0, 0 TSRMLS_CC))) {
			zephir_array_fetch_string(&_0, params, SL("id"), PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_array_update_long(&params, 0, &_0, PH_COPY | PH_SEPARATE, "phalcon/tag.zep", 451);
		}
		ZEPHIR_OBS_VAR(name);
		if (zephir_array_isset_string_fetch(&name, params, SS("name"), 0 TSRMLS_CC)) {
			if (ZEPHIR_IS_EMPTY(name)) {
				zephir_array_update_string(&params, SL("name"), &id, PH_COPY | PH_SEPARATE);
			}
		} else {
			zephir_array_update_string(&params, SL("name"), &id, PH_COPY | PH_SEPARATE);
		}
		if (!(zephir_memnstr_str(id, SL("["), "phalcon/tag.zep", 465))) {
			if (!(zephir_array_isset_string(params, SS("id")))) {
				zephir_array_update_string(&params, SL("id"), &id, PH_COPY | PH_SEPARATE);
			}
		}
		if (!(zephir_array_isset_string(params, SS("value")))) {
			ZEPHIR_CALL_SELF(&_1, "getvalue", NULL, id, params);
			zephir_check_call_status();
			zephir_array_update_string(&params, SL("value"), &_1, PH_COPY | PH_SEPARATE);
		}
	} else {
		if (!(zephir_array_isset_string(params, SS("value")))) {
			ZEPHIR_OBS_VAR(value);
			if (zephir_array_isset_long_fetch(&value, params, 0, 0 TSRMLS_CC)) {
				zephir_array_update_string(&params, SL("value"), &value, PH_COPY | PH_SEPARATE);
			}
		}
	}
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_SVS(_2, "<input type=\"", type, "\"");
	ZEPHIR_CPY_WRT(code, _2);
	zephir_is_iterable(params, &_4, &_3, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_4, (void**) &_5, &_3) == SUCCESS
	  ; zephir_hash_move_forward_ex(_4, &_3)
	) {
		ZEPHIR_GET_HMKEY(key, _4, _3);
		ZEPHIR_GET_HVALUE(value, _5);
		if (Z_TYPE_P(key) != IS_LONG) {
			ZEPHIR_INIT_LNVAR(_6);
			ZEPHIR_CONCAT_SVSVS(_6, " ", key, "=\"", value, "\"");
			zephir_concat_self(&code, _6 TSRMLS_CC);
		}
	}
	_7 = zephir_fetch_static_property_ce(phalcon_tag_ce, SL("_documentType") TSRMLS_CC);
	if (ZEPHIR_GT_LONG(_7, 5)) {
		zephir_concat_self_str(&code, SL(" />") TSRMLS_CC);
	} else {
		zephir_concat_self_str(&code, SL(">") TSRMLS_CC);
	}
	RETURN_CCTOR(code);

}

/**
 * Builds INPUT tags that implements the checked attribute
 *
 * @param   string type
 * @param	array parameters
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, _inputFieldChecked) {

	HashTable *_6;
	HashPosition _5;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *type_param = NULL, *parameters, *params = NULL, *value = NULL, *id, *key = NULL, *code = NULL, *name, *currentValue, *_0, _1, *_2, *_3, **_7, *_8 = NULL, *_9;
	zval *type = NULL, *_4;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 2, 0, &type_param, &parameters);

	zephir_get_strval(type, type_param);


	if (Z_TYPE_P(parameters) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(params);
		array_init_size(params, 2);
		zephir_array_fast_append(params, parameters);
	} else {
		ZEPHIR_CPY_WRT(params, parameters);
	}
	ZEPHIR_INIT_VAR(value);
	ZVAL_NULL(value);
	if (!(zephir_array_isset_long(params, 0))) {
		zephir_array_fetch_string(&_0, params, SL("id"), PH_NOISY | PH_READONLY TSRMLS_CC);
		zephir_array_update_long(&params, 0, &_0, PH_COPY | PH_SEPARATE, "phalcon/tag.zep", 528);
	}
	ZEPHIR_OBS_VAR(id);
	zephir_array_fetch_long(&id, params, 0, PH_NOISY TSRMLS_CC);
	if (!(zephir_array_isset_string(params, SS("name")))) {
		zephir_array_update_string(&params, SL("name"), &id, PH_COPY | PH_SEPARATE);
	} else {
		ZEPHIR_OBS_VAR(name);
		zephir_array_fetch_string(&name, params, SL("name"), PH_NOISY TSRMLS_CC);
		if (ZEPHIR_IS_EMPTY(name)) {
			zephir_array_update_string(&params, SL("name"), &id, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_SINIT_VAR(_1);
	ZVAL_STRING(&_1, "[", 0);
	ZEPHIR_INIT_VAR(_2);
	zephir_fast_strpos(_2, id, &_1, 0 );
	if (!(zephir_is_true(_2))) {
		if (!(zephir_array_isset_string(params, SS("id")))) {
			zephir_array_update_string(&params, SL("id"), &id, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_CALL_SELF(&value, "getvalue", NULL, id, params);
	zephir_check_call_status();
	if (zephir_array_isset_string(params, SS("value"))) {
		zephir_array_fetch_string(&currentValue, params, SL("value"), PH_NOISY | PH_READONLY TSRMLS_CC);
		if (ZEPHIR_IS_EQUAL(currentValue, value)) {
			ZEPHIR_INIT_BNVAR(_2);
			ZVAL_STRING(_2, "checked", 1);
			zephir_array_update_string(&params, SL("checked"), &_2, PH_COPY | PH_SEPARATE);
		}
	} else {
		if (zephir_is_true(value)) {
			ZEPHIR_INIT_VAR(_3);
			ZVAL_STRING(_3, "checked", 1);
			zephir_array_update_string(&params, SL("checked"), &_3, PH_COPY | PH_SEPARATE);
		}
		zephir_array_update_string(&params, SL("value"), &value, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(_4);
	ZEPHIR_CONCAT_SVS(_4, "<input type=\"", type, "\"");
	ZEPHIR_CPY_WRT(code, _4);
	zephir_is_iterable(params, &_6, &_5, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_6, (void**) &_7, &_5) == SUCCESS
	  ; zephir_hash_move_forward_ex(_6, &_5)
	) {
		ZEPHIR_GET_HMKEY(key, _6, _5);
		ZEPHIR_GET_HVALUE(value, _7);
		if (Z_TYPE_P(key) != IS_LONG) {
			ZEPHIR_INIT_LNVAR(_8);
			ZEPHIR_CONCAT_SVSVS(_8, " ", key, "=\"", value, "\"");
			zephir_concat_self(&code, _8 TSRMLS_CC);
		}
	}
	_9 = zephir_fetch_static_property_ce(phalcon_tag_ce, SL("_documentType") TSRMLS_CC);
	if (ZEPHIR_GT_LONG(_9, 5)) {
		zephir_concat_self_str(&code, SL(" />") TSRMLS_CC);
	} else {
		zephir_concat_self_str(&code, SL(">") TSRMLS_CC);
	}
	RETURN_CCTOR(code);

}

/**
 * Builds a HTML input[type="color"] tag
 *
 * @param array parameters
 * @return string
 */
PHP_METHOD(Phalcon_Tag, colorField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "color", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="text"] tag
 *
 * <code>
 *	echo Phalcon\Tag::textField(array("name", "size" => 30));
 * </code>
 *
 * @param	array parameters
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, textField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "text", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="number"] tag
 *
 * <code>
 *	echo Phalcon\Tag::numericField(array("price", "min" => "1", "max" => "5"));
 * </code>
 *
 * @param	array parameters
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, numericField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "number", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="range"] tag
 *
 * @param array parameters
 * @return string
 */
PHP_METHOD(Phalcon_Tag, rangeField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "range", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="email"] tag
 *
 * <code>
 *	echo Phalcon\Tag::emailField("email");
 * </code>
 *
 * @param	array parameters
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, emailField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "email", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="date"] tag
 *
 * <code>
 *	echo Phalcon\Tag::dateField(array("born", "value" => "14-12-1980"))
 * </code>
 *
 * @param	array parameters
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, dateField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "date", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="datetime"] tag
 *
 * @param array parameters
 * @return string
 */
PHP_METHOD(Phalcon_Tag, dateTimeField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "datetime", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="datetime-local"] tag
 *
 * @param array parameters
 * @return string
 */
PHP_METHOD(Phalcon_Tag, dateTimeLocalField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "datetime-local", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="month"] tag
 *
 * @param array parameters
 * @return string
 */
PHP_METHOD(Phalcon_Tag, monthField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "month", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="time"] tag
 *
 * @param array parameters
 * @return string
 */
PHP_METHOD(Phalcon_Tag, timeField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "time", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="week"] tag
 *
 * @param array parameters
 * @return string
 */
PHP_METHOD(Phalcon_Tag, weekField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "week", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="password"] tag
 *
 *<code>
 * echo Phalcon\Tag::passwordField(array("name", "size" => 30));
 *</code>
 *
 * @param	array parameters
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, passwordField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "password", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="hidden"] tag
 *
 *<code>
 * echo Phalcon\Tag::hiddenField(array("name", "value" => "mike"));
 *</code>
 *
 * @param	array parameters
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, hiddenField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "hidden", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="file"] tag
 *
 *<code>
 * echo Phalcon\Tag::fileField("file");
 *</code>
 *
 * @param	array parameters
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, fileField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "file", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="search"] tag
 *
 * @param array parameters
 * @return string
 */
PHP_METHOD(Phalcon_Tag, searchField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "search", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="tel"] tag
 *
 * @param array parameters
 * @return string
 */
PHP_METHOD(Phalcon_Tag, telField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "tel", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="url"] tag
 *
 * @param array parameters
 * @return string
 */
PHP_METHOD(Phalcon_Tag, urlField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "url", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="check"] tag
 *
 *<code>
 * echo Phalcon\Tag::checkField(array("terms", "value" => "Y"));
 *</code>
 *
 * @param	array parameters
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, checkField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "checkbox", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfieldchecked", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="radio"] tag
 *
 *<code>
 * echo Phalcon\Tag::radioField(array("wheather", "value" => "hot"))
 *</code>
 *
 * Volt syntax:
 *<code>
 * {{ radio_field("Save") }}
 *</code>
 *
 * @param	array parameters
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, radioField) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "radio", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfieldchecked", NULL, _0, parameters);
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="image"] tag
 *
 *<code>
 * echo Phalcon\Tag::imageInput(array("src" => "/img/button.png"));
 *</code>
 *
 * Volt syntax:
 *<code>
 * {{ image_input("src": "/img/button.png") }}
 *</code>
 *
 * @param	array parameters
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, imageInput) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "image", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters, ZEPHIR_GLOBAL(global_true));
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML input[type="submit"] tag
 *
 *<code>
 * echo Phalcon\Tag::submitButton("Save")
 *</code>
 *
 * Volt syntax:
 *<code>
 * {{ submit_button("Save") }}
 *</code>
 *
 * @param	array parameters
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, submitButton) {

	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	ZEPHIR_INIT_VAR(_0);
	ZVAL_STRING(_0, "submit", 0);
	ZEPHIR_RETURN_CALL_SELF("_inputfield", NULL, _0, parameters, ZEPHIR_GLOBAL(global_true));
	zephir_check_temp_parameter(_0);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML SELECT tag using a PHP array for options
 *
 *<code>
 *	echo Phalcon\Tag::selectStatic("status", array("A" => "Active", "I" => "Inactive"))
 *</code>
 *
 * @param	array parameters
 * @param   array data
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, selectStatic) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *parameters, *data = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &parameters, &data);

	if (!data) {
		data = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_RETURN_CALL_CE_STATIC(phalcon_tag_select_ce, "selectfield", &_0, parameters, data);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML SELECT tag using a Phalcon\Mvc\Model resultset as options
 *
 *<code>
 *	echo Phalcon\Tag::select(array(
 *		"robotId",
 *		Robots::find("type = "mechanical""),
 *		"using" => array("id", "name")
 * 	));
 *</code>
 *
 * Volt syntax:
 *<code>
 * {{ select("robotId", robots, "using": ["id", "name"]) }}
 *</code>
 *
 * @param	array parameters
 * @param   array data
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, select) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_0 = NULL;
	zval *parameters, *data = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &parameters, &data);

	if (!data) {
		data = ZEPHIR_GLOBAL(global_null);
	}


	ZEPHIR_RETURN_CALL_CE_STATIC(phalcon_tag_select_ce, "selectfield", &_0, parameters, data);
	zephir_check_call_status();
	RETURN_MM();

}

/**
 * Builds a HTML TEXTAREA tag
 *
 *<code>
 * echo Phalcon\Tag::textArea(array("comments", "cols" => 10, "rows" => 4))
 *</code>
 *
 * Volt syntax:
 *<code>
 * {{ text_area("comments", "cols": 10, "rows": 4) }}
 *</code>
 *
 * @param	array parameters
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, textArea) {

	HashTable *_2;
	HashPosition _1;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters, *params = NULL, *id, *key = NULL, *name, *avalue = NULL, *content = NULL, *code, *_0, **_3, *_4 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);



	if (Z_TYPE_P(parameters) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(params);
		array_init_size(params, 2);
		zephir_array_fast_append(params, parameters);
	} else {
		ZEPHIR_CPY_WRT(params, parameters);
	}
	if (!(zephir_array_isset_long(params, 0))) {
		if (zephir_array_isset_string(params, SS("id"))) {
			zephir_array_fetch_string(&_0, params, SL("id"), PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_array_update_long(&params, 0, &_0, PH_COPY | PH_SEPARATE, "phalcon/tag.zep", 952);
		}
	}
	ZEPHIR_OBS_VAR(id);
	zephir_array_fetch_long(&id, params, 0, PH_NOISY TSRMLS_CC);
	if (!(zephir_array_isset_string(params, SS("name")))) {
		zephir_array_update_string(&params, SL("name"), &id, PH_COPY | PH_SEPARATE);
	} else {
		ZEPHIR_OBS_VAR(name);
		zephir_array_fetch_string(&name, params, SL("name"), PH_NOISY TSRMLS_CC);
		if (ZEPHIR_IS_EMPTY(name)) {
			zephir_array_update_string(&params, SL("name"), &id, PH_COPY | PH_SEPARATE);
		}
	}
	if (!(zephir_array_isset_string(params, SS("id")))) {
		zephir_array_update_string(&params, SL("id"), &id, PH_COPY | PH_SEPARATE);
	}
	if (zephir_array_isset_string(params, SS("value"))) {
		ZEPHIR_OBS_VAR(content);
		zephir_array_fetch_string(&content, params, SL("value"), PH_NOISY TSRMLS_CC);
		zephir_array_unset_string(&params, SS("value"), PH_SEPARATE);
	} else {
		ZEPHIR_CALL_SELF(&content, "getvalue", NULL, id, params);
		zephir_check_call_status();
	}
	ZEPHIR_INIT_VAR(code);
	ZVAL_STRING(code, "<textarea", 1);
	zephir_is_iterable(params, &_2, &_1, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_2, (void**) &_3, &_1) == SUCCESS
	  ; zephir_hash_move_forward_ex(_2, &_1)
	) {
		ZEPHIR_GET_HMKEY(key, _2, _1);
		ZEPHIR_GET_HVALUE(avalue, _3);
		if (Z_TYPE_P(key) != IS_LONG) {
			ZEPHIR_INIT_LNVAR(_4);
			ZEPHIR_CONCAT_SVSVS(_4, " ", key, "=\"", avalue, "\"");
			zephir_concat_self(&code, _4 TSRMLS_CC);
		}
	}
	ZEPHIR_INIT_LNVAR(_4);
	ZEPHIR_CONCAT_SVS(_4, ">", content, "</textarea>");
	zephir_concat_self(&code, _4 TSRMLS_CC);
	RETURN_CCTOR(code);

}

/**
 * Builds a HTML FORM tag
 *
 * <code>
 * echo Phalcon\Tag::form("posts/save");
 * echo Phalcon\Tag::form(array("posts/save", "method" => "post"));
 * </code>
 *
 * Volt syntax:
 * <code>
 * {{ form("posts/save") }}
 * {{ form("posts/save", "method": "post") }}
 * </code>
 *
 * @param array parameters
 * @return string
 */
PHP_METHOD(Phalcon_Tag, form) {

	HashTable *_4;
	HashPosition _3;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters = NULL, *params = NULL, *paramsAction = NULL, *action = NULL, *code, *key = NULL, *avalue = NULL, *_0, *_1 = NULL, *_2 = NULL, **_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &parameters);

	ZEPHIR_SEPARATE_PARAM(parameters);


	if (Z_TYPE_P(parameters) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(params);
		array_init_size(params, 2);
		zephir_array_fast_append(params, parameters);
	} else {
		ZEPHIR_CPY_WRT(params, parameters);
	}
	ZEPHIR_OBS_VAR(paramsAction);
	if (!(zephir_array_isset_long_fetch(&paramsAction, params, 0, 0 TSRMLS_CC))) {
		ZEPHIR_OBS_NVAR(paramsAction);
		zephir_array_isset_string_fetch(&paramsAction, params, SS("action"), 0 TSRMLS_CC);
	}
	if (!(zephir_array_isset_string(params, SS("method")))) {
		ZEPHIR_INIT_VAR(_0);
		ZVAL_STRING(_0, "post", 1);
		zephir_array_update_string(&params, SL("method"), &_0, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(action);
	ZVAL_NULL(action);
	if (!(ZEPHIR_IS_EMPTY(paramsAction))) {
		ZEPHIR_CALL_SELF(&_1, "geturlservice", NULL);
		zephir_check_call_status();
		ZEPHIR_CALL_METHOD(&action, _1, "get", NULL, paramsAction);
		zephir_check_call_status();
	}
	ZEPHIR_OBS_NVAR(parameters);
	if (zephir_array_isset_string_fetch(&parameters, params, SS("parameters"), 0 TSRMLS_CC)) {
		ZEPHIR_INIT_VAR(_2);
		ZEPHIR_CONCAT_SV(_2, "?", parameters);
		zephir_concat_self(&action, _2 TSRMLS_CC);
	}
	if (!(ZEPHIR_IS_EMPTY(action))) {
		zephir_array_update_string(&params, SL("action"), &action, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(code);
	ZVAL_STRING(code, "<form", 1);
	zephir_is_iterable(params, &_4, &_3, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_4, (void**) &_5, &_3) == SUCCESS
	  ; zephir_hash_move_forward_ex(_4, &_3)
	) {
		ZEPHIR_GET_HMKEY(key, _4, _3);
		ZEPHIR_GET_HVALUE(avalue, _5);
		if (Z_TYPE_P(key) != IS_LONG) {
			ZEPHIR_INIT_LNVAR(_2);
			ZEPHIR_CONCAT_SVSVS(_2, " ", key, "=\"", avalue, "\"");
			zephir_concat_self(&code, _2 TSRMLS_CC);
		}
	}
	zephir_concat_self_str(&code, SL(">") TSRMLS_CC);
	RETURN_CCTOR(code);

}

/**
 * Builds a HTML close FORM tag
 *
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, endForm) {


	RETURN_STRING("</form>", 1);

}

/**
 * Set the title of view content
 *
 *<code>
 * Phalcon\Tag::setTitle("Welcome to my Page");
 *</code>
 *
 * @param string title
 */
PHP_METHOD(Phalcon_Tag, setTitle) {

	zval *title_param = NULL;
	zval *title = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &title_param);

	zephir_get_strval(title, title_param);


	zephir_update_static_property_ce(phalcon_tag_ce, SL("_documentTitle"), title TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Set the title separator of view content
 *
 *<code>
 * Phalcon\Tag::setTitleSeparator("-");
 *</code>
 *
 * @param string titleSeparator
 */
PHP_METHOD(Phalcon_Tag, setTitleSeparator) {

	zval *titleSeparator_param = NULL;
	zval *titleSeparator = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &titleSeparator_param);

	zephir_get_strval(titleSeparator, titleSeparator_param);


	zephir_update_static_property_ce(phalcon_tag_ce, SL("_documentTitleSeparator"), titleSeparator TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Appends a text to current document title
 *
 * @param string title
 */
PHP_METHOD(Phalcon_Tag, appendTitle) {

	zval *title_param = NULL, *_0, *_1, *_2;
	zval *title = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &title_param);

	zephir_get_strval(title, title_param);


	zephir_read_static_property_ce(&_0, phalcon_tag_ce, SL("_documentTitle") TSRMLS_CC);
	zephir_read_static_property_ce(&_1, phalcon_tag_ce, SL("_documentTitleSeparator") TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_VVV(_2, _0, _1, title);
	zephir_update_static_property_ce(phalcon_tag_ce, SL("_documentTitle"), _2 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Prepends a text to current document title
 *
 * @param string title
 */
PHP_METHOD(Phalcon_Tag, prependTitle) {

	zval *title_param = NULL, *_0, *_1, *_2;
	zval *title = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 0, &title_param);

	zephir_get_strval(title, title_param);


	zephir_read_static_property_ce(&_0, phalcon_tag_ce, SL("_documentTitleSeparator") TSRMLS_CC);
	zephir_read_static_property_ce(&_1, phalcon_tag_ce, SL("_documentTitle") TSRMLS_CC);
	ZEPHIR_INIT_VAR(_2);
	ZEPHIR_CONCAT_VVV(_2, title, _0, _1);
	zephir_update_static_property_ce(phalcon_tag_ce, SL("_documentTitle"), _2 TSRMLS_CC);
	ZEPHIR_MM_RESTORE();

}

/**
 * Gets the current document title
 *
 * <code>
 * 	echo Phalcon\Tag::getTitle();
 * </code>
 *
 * <code>
 * 	{{ get_title() }}
 * </code>
 *
 * @return string
 */
PHP_METHOD(Phalcon_Tag, getTitle) {

	zval *tags_param = NULL, *documentTitle, *_0;
	zend_bool tags;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 1, &tags_param);

	if (!tags_param) {
		tags = 1;
	} else {
		tags = zephir_get_boolval(tags_param);
	}


	ZEPHIR_OBS_VAR(documentTitle);
	zephir_read_static_property_ce(&documentTitle, phalcon_tag_ce, SL("_documentTitle") TSRMLS_CC);
	if (tags) {
		ZEPHIR_INIT_VAR(_0);
		ZEPHIR_GET_CONSTANT(_0, "PHP_EOL");
		ZEPHIR_CONCAT_SVSV(return_value, "<title>", documentTitle, "</title>", _0);
		RETURN_MM();
	}
	RETURN_CCTOR(documentTitle);

}

/**
 * Gets the current document title separator
 *
 * <code>
 *         echo Phalcon\Tag::getTitleSeparator();
 * </code>
 *
 * <code>
 *         {{ get_title_separator() }}
 * </code>
 *
 * @return string
 */
PHP_METHOD(Phalcon_Tag, getTitleSeparator) {


	RETURN_MEMBER(this_ptr, "_documentTitleSeparator");

}

/**
 * Builds a LINK[rel="stylesheet"] tag
 *
 * <code>
 * 	echo Phalcon\Tag::stylesheetLink("http://fonts.googleapis.com/css?family=Rosario", false);
 * 	echo Phalcon\Tag::stylesheetLink("css/style.css");
 * </code>
 *
 * Volt Syntax:
 *<code>
 * 	{{ stylesheet_link("http://fonts.googleapis.com/css?family=Rosario", false) }}
 * 	{{ stylesheet_link("css/style.css") }}
 *</code>
 *
 * @param	array parameters
 * @param   boolean local
 * @return	string
 */
PHP_METHOD(Phalcon_Tag, stylesheetLink) {

	HashTable *_5;
	HashPosition _4;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters = NULL, *local = NULL, *params = NULL, *code, *key = NULL, *value = NULL, *_0, *_1 = NULL, *_2 = NULL, *_3 = NULL, **_6, *_7 = NULL, *_8, *_9, *_10;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &parameters, &local);

	if (!parameters) {
		parameters = ZEPHIR_GLOBAL(global_null);
	}
	if (!local) {
		ZEPHIR_CPY_WRT(local, ZEPHIR_GLOBAL(global_true));
	} else {
		ZEPHIR_SEPARATE_PARAM(local);
	}


	if (Z_TYPE_P(parameters) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(params);
		array_init_size(params, 3);
		zephir_array_fast_append(params, parameters);
		zephir_array_fast_append(params, local);
	} else {
		ZEPHIR_CPY_WRT(params, parameters);
	}
	if (!(zephir_array_isset_string(params, SS("href")))) {
		if (zephir_array_isset_long(params, 0)) {
			zephir_array_fetch_long(&_0, params, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_array_update_string(&params, SL("href"), &_0, PH_COPY | PH_SEPARATE);
		} else {
			ZEPHIR_INIT_VAR(_1);
			ZVAL_STRING(_1, "", 1);
			zephir_array_update_string(&params, SL("href"), &_1, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_BNVAR(local);
	ZVAL_BOOL(local, 0);
	if (zephir_array_isset_long(params, 1)) {
		ZEPHIR_OBS_NVAR(local);
		zephir_array_fetch_long(&local, params, 1, PH_NOISY TSRMLS_CC);
	} else {
		if (zephir_array_isset_string(params, SS("local"))) {
			ZEPHIR_OBS_NVAR(local);
			zephir_array_fetch_string(&local, params, SL("local"), PH_NOISY TSRMLS_CC);
			zephir_array_unset_string(&params, SS("local"), PH_SEPARATE);
		}
	}
	if (!(zephir_array_isset_string(params, SS("type")))) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "text/css", 1);
		zephir_array_update_string(&params, SL("type"), &_1, PH_COPY | PH_SEPARATE);
	}
	if (zephir_is_true(local)) {
		ZEPHIR_CALL_SELF(&_2, "geturlservice", NULL);
		zephir_check_call_status();
		zephir_array_fetch_string(&_0, params, SL("href"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_3, _2, "getstatic", NULL, _0);
		zephir_check_call_status();
		zephir_array_update_string(&params, SL("href"), &_3, PH_COPY | PH_SEPARATE);
		//missing empty
	}
	ZEPHIR_INIT_VAR(code);
	ZVAL_STRING(code, "<link rel=\"stylesheet\"", 1);
	zephir_is_iterable(params, &_5, &_4, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
	  ; zephir_hash_move_forward_ex(_5, &_4)
	) {
		ZEPHIR_GET_HMKEY(key, _5, _4);
		ZEPHIR_GET_HVALUE(value, _6);
		if (Z_TYPE_P(key) != IS_LONG) {
			ZEPHIR_INIT_LNVAR(_7);
			ZEPHIR_CONCAT_SVSVS(_7, " ", key, "=\"", value, "\"");
			zephir_concat_self(&code, _7 TSRMLS_CC);
		}
	}
	_8 = zephir_fetch_static_property_ce(phalcon_tag_ce, SL("_documentType") TSRMLS_CC);
	if (ZEPHIR_GT_LONG(_8, 5)) {
		ZEPHIR_INIT_NVAR(_1);
		ZEPHIR_GET_CONSTANT(_1, "PHP_EOL");
		ZEPHIR_INIT_LNVAR(_7);
		ZEPHIR_CONCAT_SV(_7, " />", _1);
		zephir_concat_self(&code, _7 TSRMLS_CC);
	} else {
		ZEPHIR_INIT_VAR(_9);
		ZEPHIR_GET_CONSTANT(_9, "PHP_EOL");
		ZEPHIR_INIT_VAR(_10);
		ZEPHIR_CONCAT_SV(_10, ">", _9);
		zephir_concat_self(&code, _10 TSRMLS_CC);
	}
	RETURN_CCTOR(code);

}

/**
 * Builds a SCRIPT[type="javascript"] tag
 *
 * <code>
 *         echo Phalcon\Tag::javascriptInclude("http://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js", false);
 *         echo Phalcon\Tag::javascriptInclude("javascript/jquery.js");
 * </code>
 *
 * Volt syntax:
 * <code>
 * {{ javascript_include("http://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js", false) }}
 * {{ javascript_include("javascript/jquery.js") }}
 * </code>
 *
 * @param array parameters
 * @param   boolean local
 * @return string
 */
PHP_METHOD(Phalcon_Tag, javascriptInclude) {

	HashTable *_5;
	HashPosition _4;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters = NULL, *local = NULL, *params = NULL, *code, *key = NULL, *value = NULL, *_0, *_1 = NULL, *_2 = NULL, *_3 = NULL, **_6, *_7 = NULL;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &parameters, &local);

	if (!parameters) {
		parameters = ZEPHIR_GLOBAL(global_null);
	}
	if (!local) {
		ZEPHIR_CPY_WRT(local, ZEPHIR_GLOBAL(global_true));
	} else {
		ZEPHIR_SEPARATE_PARAM(local);
	}


	if (Z_TYPE_P(parameters) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(params);
		array_init_size(params, 3);
		zephir_array_fast_append(params, parameters);
		zephir_array_fast_append(params, local);
	} else {
		ZEPHIR_CPY_WRT(params, parameters);
	}
	if (!(zephir_array_isset_string(params, SS("src")))) {
		if (zephir_array_isset_long(params, 0)) {
			zephir_array_fetch_long(&_0, params, 0, PH_NOISY | PH_READONLY TSRMLS_CC);
			zephir_array_update_string(&params, SL("src"), &_0, PH_COPY | PH_SEPARATE);
		} else {
			ZEPHIR_INIT_VAR(_1);
			ZVAL_STRING(_1, "", 1);
			zephir_array_update_string(&params, SL("src"), &_1, PH_COPY | PH_SEPARATE);
		}
	}
	ZEPHIR_INIT_BNVAR(local);
	ZVAL_BOOL(local, 0);
	if (zephir_array_isset_long(params, 1)) {
		ZEPHIR_OBS_NVAR(local);
		zephir_array_fetch_long(&local, params, 1, PH_NOISY TSRMLS_CC);
	} else {
		if (zephir_array_isset_string(params, SS("local"))) {
			ZEPHIR_OBS_NVAR(local);
			zephir_array_fetch_string(&local, params, SL("local"), PH_NOISY TSRMLS_CC);
			zephir_array_unset_string(&params, SS("local"), PH_SEPARATE);
		}
	}
	if (!(zephir_array_isset_string(params, SS("type")))) {
		ZEPHIR_INIT_NVAR(_1);
		ZVAL_STRING(_1, "text/javascript", 1);
		zephir_array_update_string(&params, SL("type"), &_1, PH_COPY | PH_SEPARATE);
	}
	if (zephir_is_true(local)) {
		ZEPHIR_CALL_SELF(&_2, "geturlservice", NULL);
		zephir_check_call_status();
		zephir_array_fetch_string(&_0, params, SL("src"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_3, _2, "getstatic", NULL, _0);
		zephir_check_call_status();
		zephir_array_update_string(&params, SL("src"), &_3, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(code);
	ZVAL_STRING(code, "<script", 1);
	zephir_is_iterable(params, &_5, &_4, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
	  ; zephir_hash_move_forward_ex(_5, &_4)
	) {
		ZEPHIR_GET_HMKEY(key, _5, _4);
		ZEPHIR_GET_HVALUE(value, _6);
		if (Z_TYPE_P(key) != IS_LONG) {
			ZEPHIR_INIT_LNVAR(_7);
			ZEPHIR_CONCAT_SVSVS(_7, " ", key, "=\"", value, "\"");
			zephir_concat_self(&code, _7 TSRMLS_CC);
		}
	}
	ZEPHIR_INIT_NVAR(_1);
	ZEPHIR_GET_CONSTANT(_1, "PHP_EOL");
	ZEPHIR_INIT_LNVAR(_7);
	ZEPHIR_CONCAT_SV(_7, "></script>", _1);
	zephir_concat_self(&code, _7 TSRMLS_CC);
	RETURN_CCTOR(code);

}

/**
 * Builds HTML IMG tags
 *
 * <code>
 *         echo Phalcon\Tag::image("img/bg.png");
 *         echo Phalcon\Tag::image(array("img/photo.jpg", "alt" => "Some Photo"));
 * </code>
 *
 * Volt Syntax:
 * <code>
 *         {{ image("img/bg.png") }}
 *         {{ image("img/photo.jpg", "alt": "Some Photo") }}
 *         {{ image("http://static.mywebsite.com/img/bg.png", false) }}
 * </code>
 *
 * @param  array parameters
 * @param  boolean local
 * @return string
 */
PHP_METHOD(Phalcon_Tag, image) {

	HashTable *_5;
	HashPosition _4;
	int ZEPHIR_LAST_CALL_STATUS;
	zval *parameters = NULL, *local = NULL, *params = NULL, *code, *key = NULL, *value = NULL, *src, *_0, *_1 = NULL, *_2 = NULL, *_3, **_6, *_7 = NULL, *_8;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 0, 2, &parameters, &local);

	if (!parameters) {
		parameters = ZEPHIR_GLOBAL(global_null);
	}
	if (!local) {
		local = ZEPHIR_GLOBAL(global_true);
	}


	if (Z_TYPE_P(parameters) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(params);
		array_init_size(params, 2);
		zephir_array_fast_append(params, parameters);
	} else {
		ZEPHIR_CPY_WRT(params, parameters);
	}
	if (!(zephir_array_isset_string(params, SS("src")))) {
		ZEPHIR_OBS_VAR(src);
		if (zephir_array_isset_long_fetch(&src, params, 0, 0 TSRMLS_CC)) {
			zephir_array_update_string(&params, SL("src"), &src, PH_COPY | PH_SEPARATE);
		} else {
			ZEPHIR_INIT_VAR(_0);
			ZVAL_STRING(_0, "", 1);
			zephir_array_update_string(&params, SL("src"), &_0, PH_COPY | PH_SEPARATE);
		}
	}
	if (zephir_is_true(local)) {
		ZEPHIR_CALL_SELF(&_1, "geturlservice", NULL);
		zephir_check_call_status();
		zephir_array_fetch_string(&_3, params, SL("src"), PH_NOISY | PH_READONLY TSRMLS_CC);
		ZEPHIR_CALL_METHOD(&_2, _1, "getstatic", NULL, _3);
		zephir_check_call_status();
		zephir_array_update_string(&params, SL("src"), &_2, PH_COPY | PH_SEPARATE);
	}
	ZEPHIR_INIT_VAR(code);
	ZVAL_STRING(code, "<img", 1);
	zephir_is_iterable(params, &_5, &_4, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_5, (void**) &_6, &_4) == SUCCESS
	  ; zephir_hash_move_forward_ex(_5, &_4)
	) {
		ZEPHIR_GET_HMKEY(key, _5, _4);
		ZEPHIR_GET_HVALUE(value, _6);
		if (Z_TYPE_P(key) != IS_LONG) {
			ZEPHIR_INIT_LNVAR(_7);
			ZEPHIR_CONCAT_SVSVS(_7, " ", key, "=\"", value, "\"");
			zephir_concat_self(&code, _7 TSRMLS_CC);
		}
	}
	_8 = zephir_fetch_static_property_ce(phalcon_tag_ce, SL("_documentType") TSRMLS_CC);
	if (ZEPHIR_GT_LONG(_8, 5)) {
		zephir_concat_self_str(&code, SL(" />") TSRMLS_CC);
	} else {
		zephir_concat_self_str(&code, SL(">") TSRMLS_CC);
	}
	RETURN_CCTOR(code);

}

/**
 * Converts texts into URL-friendly titles
 *
 *<code>
 * echo Phalcon\Tag::friendlyTitle("These are big important news", "-")
 *</code>
 *
 * @param string text
 * @param string separator
 * @param boolean lowercase
 * @return text
 */
PHP_METHOD(Phalcon_Tag, friendlyTitle) {

	int ZEPHIR_LAST_CALL_STATUS;
	zephir_nts_static zephir_fcall_cache_entry *_1 = NULL;
	zval *text, *separator = NULL, *lowercase = NULL, *friendly = NULL, _0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 2, &text, &separator, &lowercase);

	if (!separator) {
		ZEPHIR_INIT_VAR(separator);
		ZVAL_STRING(separator, "-", 1);
	}
	if (!lowercase) {
		lowercase = ZEPHIR_GLOBAL(global_true);
	}


	ZEPHIR_SINIT_VAR(_0);
	ZVAL_STRING(&_0, "~[^a-z0-9A-Z]+~", 0);
	ZEPHIR_CALL_FUNCTION(&friendly, "preg_replace", &_1, &_0, separator, text);
	zephir_check_call_status();
	if (!(ZEPHIR_IS_EMPTY(lowercase))) {
		zephir_fast_strtolower(return_value, friendly);
		RETURN_MM();
	}
	RETURN_CCTOR(friendly);

}

/**
 * Set the document type of content
 *
 * @param string doctype
 */
PHP_METHOD(Phalcon_Tag, setDocType) {

	zval *doctype;

	zephir_fetch_params(0, 1, 0, &doctype);



	zephir_update_static_property_ce(phalcon_tag_ce, SL("_documentType"), doctype TSRMLS_CC);

}

/**
 * Get the document type declaration of content
 *
 * @return string
 */
PHP_METHOD(Phalcon_Tag, getDocType) {

	zval *_0, *_1 = NULL, *_2 = NULL;

	ZEPHIR_MM_GROW();

	_0 = zephir_fetch_static_property_ce(phalcon_tag_ce, SL("_documentType") TSRMLS_CC);
	do {
		if (ZEPHIR_IS_LONG(_0, 1)) {
			ZEPHIR_INIT_VAR(_1);
			ZEPHIR_GET_CONSTANT(_1, "PHP_EOL");
			ZEPHIR_CONCAT_SV(return_value, "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 3.2 Final//EN\">", _1);
			RETURN_MM();
		}
		if (ZEPHIR_IS_LONG(_0, 2)) {
			ZEPHIR_INIT_NVAR(_1);
			ZEPHIR_GET_CONSTANT(_1, "PHP_EOL");
			ZEPHIR_INIT_VAR(_2);
			ZEPHIR_GET_CONSTANT(_2, "PHP_EOL");
			ZEPHIR_CONCAT_SVSV(return_value, "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01//EN\"", _1, "\t\"http://www.w3.org/TR/html4/strict.dtd\">", _2);
			RETURN_MM();
		}
		if (ZEPHIR_IS_LONG(_0, 3)) {
			ZEPHIR_INIT_NVAR(_1);
			ZEPHIR_GET_CONSTANT(_1, "PHP_EOL");
			ZEPHIR_INIT_NVAR(_2);
			ZEPHIR_GET_CONSTANT(_2, "PHP_EOL");
			ZEPHIR_CONCAT_SVSV(return_value, "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\"", _1, "\t\"http://www.w3.org/TR/html4/loose.dtd\">", _2);
			RETURN_MM();
		}
		if (ZEPHIR_IS_LONG(_0, 4)) {
			ZEPHIR_INIT_NVAR(_1);
			ZEPHIR_GET_CONSTANT(_1, "PHP_EOL");
			ZEPHIR_INIT_NVAR(_2);
			ZEPHIR_GET_CONSTANT(_2, "PHP_EOL");
			ZEPHIR_CONCAT_SVSV(return_value, "<!DOCTYPE html PUBLIC \"-//W3C//DTD HTML 4.01 Frameset//EN\"", _1, "\t\"http://www.w3.org/TR/html4/frameset.dtd\">", _2);
			RETURN_MM();
		}
		if (ZEPHIR_IS_LONG(_0, 5)) {
			ZEPHIR_INIT_NVAR(_1);
			ZEPHIR_GET_CONSTANT(_1, "PHP_EOL");
			ZEPHIR_CONCAT_SV(return_value, "<!DOCTYPE html>", _1);
			RETURN_MM();
		}
		if (ZEPHIR_IS_LONG(_0, 6)) {
			ZEPHIR_INIT_NVAR(_1);
			ZEPHIR_GET_CONSTANT(_1, "PHP_EOL");
			ZEPHIR_INIT_NVAR(_2);
			ZEPHIR_GET_CONSTANT(_2, "PHP_EOL");
			ZEPHIR_CONCAT_SVSV(return_value, "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Strict//EN\"", _1, "\t\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-strict.dtd\">", _2);
			RETURN_MM();
		}
		if (ZEPHIR_IS_LONG(_0, 7)) {
			ZEPHIR_INIT_NVAR(_1);
			ZEPHIR_GET_CONSTANT(_1, "PHP_EOL");
			ZEPHIR_INIT_NVAR(_2);
			ZEPHIR_GET_CONSTANT(_2, "PHP_EOL");
			ZEPHIR_CONCAT_SVSV(return_value, "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Transitional//EN\"", _1, "\t\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">", _2);
			RETURN_MM();
		}
		if (ZEPHIR_IS_LONG(_0, 8)) {
			ZEPHIR_INIT_NVAR(_1);
			ZEPHIR_GET_CONSTANT(_1, "PHP_EOL");
			ZEPHIR_INIT_NVAR(_2);
			ZEPHIR_GET_CONSTANT(_2, "PHP_EOL");
			ZEPHIR_CONCAT_SVSV(return_value, "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.0 Frameset//EN\"", _1, "\t\"http://www.w3.org/TR/xhtml1/DTD/xhtml1-frameset.dtd\">", _2);
			RETURN_MM();
		}
		if (ZEPHIR_IS_LONG(_0, 9)) {
			ZEPHIR_INIT_NVAR(_1);
			ZEPHIR_GET_CONSTANT(_1, "PHP_EOL");
			ZEPHIR_INIT_NVAR(_2);
			ZEPHIR_GET_CONSTANT(_2, "PHP_EOL");
			ZEPHIR_CONCAT_SVSV(return_value, "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1//EN\"", _1, "\t\"http://www.w3.org/TR/xhtml11/DTD/xhtml11.dtd\">", _2);
			RETURN_MM();
		}
		if (ZEPHIR_IS_LONG(_0, 10)) {
			ZEPHIR_INIT_NVAR(_1);
			ZEPHIR_GET_CONSTANT(_1, "PHP_EOL");
			ZEPHIR_INIT_NVAR(_2);
			ZEPHIR_GET_CONSTANT(_2, "PHP_EOL");
			ZEPHIR_CONCAT_SVSV(return_value, "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 2.0//EN\"", _1, "\t\"http://www.w3.org/MarkUp/DTD/xhtml2.dtd\">", _2);
			RETURN_MM();
		}
	} while(0);

	RETURN_MM_STRING("", 1);

}

/**
 * Builds a HTML tag
 *
 *<code>
 *        echo Phalcon\Tag::tagHtml(name, parameters, selfClose, onlyStart, eol);
 *</code>
 *
 * @param string tagName
 * @param array parameters
 * @param boolean selfClose
 * @param boolean onlyStart
 * @param boolean useEol
 * @return string
 */
PHP_METHOD(Phalcon_Tag, tagHtml) {

	HashTable *_1;
	HashPosition _0;
	zval *tagName, *parameters = NULL, *selfClose = NULL, *onlyStart = NULL, *useEol = NULL, *params = NULL, *localCode, *key = NULL, *value = NULL, **_2, *_3 = NULL, *_4, *_5;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 4, &tagName, &parameters, &selfClose, &onlyStart, &useEol);

	if (!parameters) {
		parameters = ZEPHIR_GLOBAL(global_null);
	}
	if (!selfClose) {
		selfClose = ZEPHIR_GLOBAL(global_false);
	}
	if (!onlyStart) {
		onlyStart = ZEPHIR_GLOBAL(global_false);
	}
	if (!useEol) {
		useEol = ZEPHIR_GLOBAL(global_false);
	}


	if (Z_TYPE_P(parameters) != IS_ARRAY) {
		ZEPHIR_INIT_VAR(params);
		array_init_size(params, 2);
		zephir_array_fast_append(params, parameters);
	} else {
		ZEPHIR_CPY_WRT(params, parameters);
	}
	ZEPHIR_INIT_VAR(localCode);
	ZEPHIR_CONCAT_SV(localCode, "<", tagName);
	zephir_is_iterable(params, &_1, &_0, 0, 0);
	for (
	  ; zephir_hash_get_current_data_ex(_1, (void**) &_2, &_0) == SUCCESS
	  ; zephir_hash_move_forward_ex(_1, &_0)
	) {
		ZEPHIR_GET_HMKEY(key, _1, _0);
		ZEPHIR_GET_HVALUE(value, _2);
		if (Z_TYPE_P(key) != IS_LONG) {
			ZEPHIR_INIT_LNVAR(_3);
			ZEPHIR_CONCAT_SVSVS(_3, " ", key, "=\"", value, "\"");
			zephir_concat_self(&localCode, _3 TSRMLS_CC);
		}
	}
	_4 = zephir_fetch_static_property_ce(phalcon_tag_ce, SL("_documentType") TSRMLS_CC);
	if (ZEPHIR_GT_LONG(_4, 5)) {
		if (zephir_is_true(selfClose)) {
			zephir_concat_self_str(&localCode, SL(" />") TSRMLS_CC);
		} else {
			zephir_concat_self_str(&localCode, SL(">") TSRMLS_CC);
		}
	} else {
		if (zephir_is_true(onlyStart)) {
			zephir_concat_self_str(&localCode, SL(">") TSRMLS_CC);
		} else {
			ZEPHIR_INIT_LNVAR(_3);
			ZEPHIR_CONCAT_SVS(_3, "></", tagName, ">");
			zephir_concat_self(&localCode, _3 TSRMLS_CC);
		}
	}
	if (zephir_is_true(useEol)) {
		ZEPHIR_INIT_VAR(_5);
		ZEPHIR_GET_CONSTANT(_5, "PHP_EOL");
		zephir_concat_self(&localCode, _5 TSRMLS_CC);
	}
	RETURN_CCTOR(localCode);

}

/**
 * Builds a HTML tag closing tag
 *
 *<code>
 *        echo Phalcon\Tag::tagHtmlClose("script", true)
 *</code>
 *
 * @param string tagName
 * @param boolean useEol
 * @return string
 */
PHP_METHOD(Phalcon_Tag, tagHtmlClose) {

	zval *tagName, *useEol = NULL, *_0;

	ZEPHIR_MM_GROW();
	zephir_fetch_params(1, 1, 1, &tagName, &useEol);

	if (!useEol) {
		useEol = ZEPHIR_GLOBAL(global_false);
	}


	if (zephir_is_true(useEol)) {
		ZEPHIR_INIT_VAR(_0);
		ZEPHIR_GET_CONSTANT(_0, "PHP_EOL");
		ZEPHIR_CONCAT_SVSV(return_value, "</", tagName, ">", _0);
		RETURN_MM();
	}
	ZEPHIR_CONCAT_SVS(return_value, "</", tagName, ">");
	RETURN_MM();

}

