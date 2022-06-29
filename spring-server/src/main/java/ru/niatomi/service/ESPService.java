package ru.niatomi.service;

import org.springframework.stereotype.Service;
import ru.niatomi.model.dto.ReferenceDataDto;
import ru.niatomi.model.dto.SensorsDto;
import ru.niatomi.model.dto.TimeScheduleDto;

import java.util.List;

/**
 * @author niatomi
 */
@Service
public interface ESPService {

    ReferenceDataDto getReferenceData();

    void getTimeSchedule(SensorsDto sensorsDto);

    List<TimeScheduleDto> getTimeSchedule();

}
