package ru.niatomi.repository;

import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.stereotype.Repository;
import ru.niatomi.model.domain.arduinoConfig.ReferenceData;

import java.util.Optional;

/**
 * @author niatomi
 */
@Repository
public interface ReferenceDataRepository extends MongoRepository<ReferenceData, Integer> {
}
