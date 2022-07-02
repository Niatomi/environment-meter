package ru.niatomi.service.Impl;

import lombok.AllArgsConstructor;
import lombok.NoArgsConstructor;
import org.springframework.stereotype.Service;
import ru.niatomi.model.dto.ReferenceDataDto;
import ru.niatomi.model.dto.SensorsDto;
import ru.niatomi.model.dto.TimeScheduleDto;
import ru.niatomi.service.ESPService;

import java.util.List;

/**
 * @author niatomi
 */
@Service
@AllArgsConstructor
public class ESPServiceImpl implements ESPService {

    @Override
    public ReferenceDataDto getReferenceData() {
        return null;
    }

    @Override
    public void saveSensorData(SensorsDto sensorsDto) {
        Sensors map = sensorsMapper.map(sensorsDto);
        sensorsRepository.save(map);
    }

    @Override
    public List<TimeScheduleDto> getTimeSchedule() {
        return null;
    }
}
