/**
 * GNU GENERAL PUBLIC LICENSE
 * Version 3, 29 June 2007
 *
 * Copyright (C) 2007 Free Software Foundation, Inc. <https://fsf.org/>
 * For more information on this, and how to apply and follow the GNU GPL, see
 * <https://www.gnu.org/licenses/>
 */

/// @file caviar.h

#ifndef CAVIAR_CAVIAR_H
#define CAVIAR_CAVIAR_H

#include "fsd.h"

namespace caviar {
  void summarize(std::string&& p_filename);
  void truncate(const std::string& p_filename);

} // namespace caviar

#endif //CAVIAR_CAVIAR_H
