package ru.niatomi.service.Impl;

import lombok.AllArgsConstructor;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;
import ru.niatomi.mapper.ReferenceDataMapper;
import ru.niatomi.mapper.SensorsMapper;
import ru.niatomi.model.domain.sensor.Sensors;
import ru.niatomi.model.domain.arduinoConfig.ReferenceData;
import ru.niatomi.model.dto.ReferenceDataDto;
import ru.niatomi.model.dto.SensorsDto;
import ru.niatomi.model.dto.TimeScheduleDto;
import ru.niatomi.repository.ReferenceDataRepository;
import ru.niatomi.repository.SensorsRepository;
import ru.niatomi.service.ESPService;

import javax.annotation.PostConstruct;
import java.util.List;
import java.util.Optional;

/**
 * @author niatomi
 */
@Service
@AllArgsConstructor
public class ESPServiceImpl implements ESPService {

    private final SensorsMapper sensorsMapper;
    private final SensorsRepository sensorsRepository;

    private final ReferenceDataRepository referenceDataRepository;
    private final ReferenceDataMapper referenceDataMapper;

    @Override
    public ReferenceDataDto getReferenceData() {
        Optional<ReferenceData> byId = referenceDataRepository.findById(1);
        ReferenceData referenceData = byId.get();
        return referenceDataMapper.map(referenceData);
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
