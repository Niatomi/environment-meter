package ru.niatomi.model.dto.time;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;
import org.springframework.data.mongodb.core.aggregation.DateOperators;

import java.time.DayOfWeek;

/**
 * @author niatomi
 */
@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
public class TimePlanDto {

    private DayOfWeek dayOfWeek;
    private DateOperators.DayOfMonth dayOfMonth;
    private Integer hours;
    private Integer minutes;
    private Integer seconds;

}
