package ru.niatomi.model.domain.schedule;

import lombok.*;

import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;

/**
 * @author niatomi
 */
@Getter
@Setter
@AllArgsConstructor
@NoArgsConstructor
@ToString
public class ScheduleConfiguration {

    private Integer id;

    // TODO: instance choose between ScheduleConfigs

}
