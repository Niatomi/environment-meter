package ru.niatomi.repository;

import org.springframework.data.mongodb.repository.MongoRepository;
import ru.niatomi.model.domain.arduinoConfig.UpdatableConfig;

/**
 * @author niatomi
 */
public interface UpdatableConfigRepository extends MongoRepository<UpdatableConfig, Integer> {
}
