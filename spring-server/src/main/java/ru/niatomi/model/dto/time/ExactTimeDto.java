package ru.niatomi.model.dto.time;

import lombok.*;
import sun.util.calendar.Era;

import java.time.Month;
import java.time.Year;

/**
 * @author niatomi
 */
@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
public class ExactTimeDto {

    private Month month;
    private Integer day;
    private Integer hours;
    private Integer minutes;
    private Integer seconds;

}
