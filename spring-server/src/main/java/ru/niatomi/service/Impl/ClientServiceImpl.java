package ru.niatomi.service.Impl;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;
import org.springframework.stereotype.Service;
import ru.niatomi.mapper.ReferenceDataMapper;
import ru.niatomi.model.domain.arduinoConfig.ReferenceData;
import ru.niatomi.model.dto.data.DataDto;
import ru.niatomi.model.dto.time.ExactTimeDto;
import ru.niatomi.model.dto.time.TimePlanAndExactDto;
import ru.niatomi.model.dto.time.TimePlanDto;
import ru.niatomi.repository.SensorsRepository;
import ru.niatomi.repository.UpdatableConfigRepository;
import ru.niatomi.service.ClientService;

/**
 * @author niatomi
 */
@AllArgsConstructor
@Getter
@Setter
@Service
public class ClientServiceImpl implements ClientService {

    private final UpdatableConfigRepository updatableConfigRepository;
    private final SensorsRepository sensorsRepository;
    private final ReferenceDataRepository referenceDataRepository;

    private final ExactTimeRepository exactTimeRepository;
    private final PeriodTimeRepository periodTimeRepository;

    private final ReferenceDataMapper referenceDataMapper;

    @Override
    public String updateReferenceData(ReferenceDataDto referenceData) {
        ReferenceData map = referenceDataMapper.map(referenceData);
        map.setId(1);
        referenceDataRepository.save(map);
        return "Data saved";
    }

    @Override
    public String addExactTime(ExactTimeDto exactTimeDto) {
        ExactTime exactTime = new ExactTime(
                exactTimeRepository.count() + 1,
                LocalDateTime.of(
                        LocalDateTime.now().getYear(),
                        exactTimeDto.getMonth(),
                        exactTimeDto.getDay(),
                        exactTimeDto.getHours(),
                        exactTimeDto.getMinutes(),
                        exactTimeDto.getSeconds()
                ));

        exactTimeRepository.save(exactTime);
        return "Exact time saved";
    }

    @Override
    public String addTimePlan(TimePlanDto timePlanDto) {
        return null;
    }

    @Override
    public TimePlanAndExactDto getAllTime() {
        return null;
    }

    @Override
    public DataDto getData() {
        return null;
    }
}
