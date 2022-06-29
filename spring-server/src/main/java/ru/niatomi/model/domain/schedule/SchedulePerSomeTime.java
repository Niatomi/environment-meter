package ru.niatomi.model.domain.schedule;

import lombok.*;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import java.time.LocalDateTime;
import java.util.List;

/**
 * @author niatomi
 */
@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@ToString
public class SchedulePerSomeTime {

    private Integer id;

    private Integer perDays;

    private List<LocalDateTime> checkTime;

}
