package ru.niatomi.service.Impl;

import lombok.AllArgsConstructor;
import lombok.Getter;
import lombok.Setter;
import org.springframework.stereotype.Service;
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

    @Override
    public String updateReferenceData(ReferenceData referenceData) {
        return null;
    }

    @Override
    public String addExactTime(ExactTimeDto exactTimeDto) {
        return null;
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
