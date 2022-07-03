package ru.niatomi.service.Impl;

import lombok.AllArgsConstructor;
import org.springframework.stereotype.Service;
import ru.niatomi.mapper.ReferenceDataMapper;
import ru.niatomi.mapper.SensorsMapper;
import ru.niatomi.model.domain.sensor.Sensors;
import ru.niatomi.model.domain.arduinoConfig.ReferenceData;
import ru.niatomi.model.dto.ReferenceDataDto;
import ru.niatomi.model.dto.SensorsDto;
import ru.niatomi.model.dto.TimeScheduleDto;
import ru.niatomi.model.dto.UpdatableDto;
import ru.niatomi.repository.ReferenceDataRepository;
import ru.niatomi.repository.SensorsRepository;
import ru.niatomi.service.ESPService;

import java.time.LocalDateTime;
import java.time.ZoneOffset;
import java.util.ArrayList;
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

    /*
    * TimeScheduleDto должен быть всегда отсортирован по возростанию
    * ESP итерируется по json объекту без проверки на минимальное значение
    */
    @Override
    public TimeScheduleDto getTimeSchedule() {
        TimeScheduleDto schedule = new TimeScheduleDto();
        List<Long> unixTime = new ArrayList<>();
        for (int i = 1; i <= 10; i++) {
            unixTime.add(LocalDateTime.now().plusMinutes(2*i).toEpochSecond(ZoneOffset.of("+04:00")));
        }
        schedule.setListOfSchedules(unixTime);
        return schedule;
    }

    @Override
    public UpdatableDto checkOnReferenceUpdate() {
        ReferenceData referenceData = referenceDataRepository.findById(1).get();
        return new UpdatableDto(referenceData.isUpdated());
    }

    @Override
    public void stateReferenceUpdate() {
        ReferenceData referenceData = referenceDataRepository.findById(1).get();
        referenceData.setUpdated(false);
        referenceDataRepository.save(referenceData);
    }


    // TODO: реализовать тут логику
    @Override
    public UpdatableDto checkOnTimeReferenceUpdate() {
        return null;
    }

    @Override
    public void stateTimeReferenceUpdate() {

    }
}
