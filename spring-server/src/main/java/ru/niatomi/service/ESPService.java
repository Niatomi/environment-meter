package ru.niatomi.service;

import org.springframework.stereotype.Service;
import ru.niatomi.model.dto.configFiles.ReferenceDataDto;
import ru.niatomi.model.dto.configFiles.SensorsDto;
import ru.niatomi.model.dto.time.TimeScheduleDto;
import ru.niatomi.model.dto.configFiles.UpdatableDto;

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
