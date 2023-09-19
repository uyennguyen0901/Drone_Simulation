#ifndef Charger_FACTORY_H_
#define Charger_FACTORY_H_

#include <vector>

#include "IEntityFactory.h"
#include "Charger.h"

/**
 * @brief Charger Factory to produce Charger class.
 */
class ChargerFactory : public IEntityFactory {
 public:
  /**
   * @brief Destructor for ChargerFactory class.
   */
  virtual ~ChargerFactory() {}

  /**
   * @brief Creates entity using the given JSON object, if possible.
   * @param entity - JsonObject to be used to create the new entity.
   * @return Entity that was created if it was created successfully, or a nullpointer if creation failed.
   */
  IEntity* CreateEntity(JsonObject& entity);
};

#endif  // CHARGER_FACTORY_H_
