package ru.niatomi.model.dto;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.util.List;

/**
 * @author niatomi
 */
@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
public class TimeScheduleDto {

    private List<Long> listOfSchedules;

}
