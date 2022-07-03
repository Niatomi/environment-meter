package ru.niatomi.service;

import org.springframework.stereotype.Service;
import ru.niatomi.model.dto.ReferenceDataDto;
import ru.niatomi.model.dto.SensorsDto;
import ru.niatomi.model.dto.TimeScheduleDto;
import ru.niatomi.model.dto.UpdatableDto;

/**
 * @author niatomi
 */
@Service
public interface ESPService {

    ReferenceDataDto getReferenceData();

    void saveSensorData(SensorsDto sensorsDto);

    TimeScheduleDto getTimeSchedule();

    UpdatableDto checkOnReferenceUpdate();

    void stateReferenceUpdate();

    UpdatableDto checkOnTimeReferenceUpdate();

    void stateTimeReferenceUpdate();

}
