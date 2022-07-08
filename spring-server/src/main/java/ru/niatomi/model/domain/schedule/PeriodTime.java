package ru.niatomi.model.domain.schedule;

import lombok.AllArgsConstructor;
import lombok.Data;
import org.springframework.data.mongodb.core.mapping.Document;
import ru.niatomi.model.domain.validation.I2CCheckTimeRestrictions;

import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import java.time.LocalDateTime;

/**
 * @author niatomi
 */
@Document
@Data
@AllArgsConstructor
public class PeriodTime {

    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Long id;

    private Long startTime;

    @I2CCheckTimeRestrictions
    private Long periodTime;

}
