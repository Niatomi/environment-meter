package ru.niatomi.repository;

import org.springframework.data.mongodb.repository.MongoRepository;
import ru.niatomi.model.domain.schedule.PeriodTime;

/**
 * @author niatomi
 */
public interface PeriodTimeRepository extends MongoRepository<PeriodTime, Integer> {
}
