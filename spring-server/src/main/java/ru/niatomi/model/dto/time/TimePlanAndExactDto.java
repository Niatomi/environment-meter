package ru.niatomi.model.dto.time;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.NoArgsConstructor;
import lombok.Setter;

import java.util.List;
import java.util.Optional;

/**
 * @author niatomi
 */
@AllArgsConstructor
@NoArgsConstructor
@Getter
@Setter
public class TimePlanAndExactDto {

    private Optional<List<ExactTimeDto>> exactTimeDto;
    private Optional<List<TimePlanDto>> timePlanDto;

}
