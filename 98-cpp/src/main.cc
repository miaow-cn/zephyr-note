#include "00_ref.h"
#include "01_class.h"
#include "02_static.h"
#include "03_constructor.h"
#include "04_destructor.h"
#include "05_inherit.h"
#include "06_virtual.h"
#include "07_pure_virtual.h"
#include "08_create_object.h"
#include "09_explicit_conversion.h"
#include "10_operator_overload.h"
#include "11_this.h"
#include "12_smart_pointer.h"
#include "13_copy_constructor.h"
#include "14_arrow_operator.h"
#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>
#include <iostream>

LOG_MODULE_REGISTER(98_cpp, LOG_LEVEL_INF);

int main()
{
	LOG_INF("Starting C++ examples...");

	ref_entry();
	_01_class::Entry();
	_02_static::Entry();
	_03_constructor::Entry();
	_04_destructor::Entry();
	_05_inherit::Entry();
	_06_virtual::Entry();
	_07_pure_virtual::Entry();
	_08_create_object::Entry();
	_09_explicit_conversion::Entry();
	_10_operator_overload::Entry();
	_11_this::Entry();
	_12_smart_pointer::Entry();
	_13_copy_constructor::Entry();
	_14_arrow_operator::Entry();

	return 0;
}
