package ru.niatomi.repository;

import org.springframework.data.mongodb.repository.MongoRepository;
import ru.niatomi.model.domain.schedule.ExactTime;

/**
 * @author niatomi
 */
public interface ExactTimeRepository extends MongoRepository<ExactTime, Integer> {
}
