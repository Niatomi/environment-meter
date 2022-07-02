package ru.niatomi.repository;

import org.springframework.data.mongodb.repository.MongoRepository;
import org.springframework.data.repository.CrudRepository;
import org.springframework.stereotype.Repository;
import ru.niatomi.model.domain.sensor.Sensors;

/**
 * @author niatomi
 */
@Repository
public interface SensorsRepository extends CrudRepository<Sensors, Long> {
}
