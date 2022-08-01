package ru.niatomi.service.Impl;

import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.Getter;
import lombok.Setter;
import org.springframework.stereotype.Service;
import ru.niatomi.mapper.ReferenceDataMapper;
import ru.niatomi.mapper.SensorsMapper;
import ru.niatomi.model.domain.arduinoConfig.ReferenceData;
import ru.niatomi.model.domain.schedule.ExactTime;
import ru.niatomi.model.domain.schedule.PeriodTime;
import ru.niatomi.model.dto.configFiles.ReferenceDataDto;
import ru.niatomi.model.dto.data.DataDto;
import ru.niatomi.model.dto.time.ExactTimeDto;
import ru.niatomi.model.dto.time.TimePlanAndExactDto;
import ru.niatomi.model.dto.time.TimePlanDto;
import ru.niatomi.repository.*;
import ru.niatomi.service.ClientService;

import java.text.DecimalFormat;
import java.time.LocalDateTime;
import java.util.ArrayList;
import java.util.List;

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
    private final SensorsMapper sensorsMapper;

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
//        PeriodTime periodTime = new PeriodTime(
//                periodTimeRepository.count() + 1,
//                timePlanDto.
//        );
        return null;
    }

    @Override
    public TimePlanAndExactDto getAllTime() {
        return null;
    }

    @Override
    public List<DataDto> getData() {
        List<DataDto> dataDtos = new ArrayList<>();

        sensorsRepository.findAll().forEach(sensors -> {
            sensors.setEnvironmentTemperature(
            Double.parseDouble(sensors
                    .getEnvironmentTemperature()
                    .toString()
                    .substring(
                            0,
                            sensors
                                    .getEnvironmentTemperature()
                                    .toString()
                                    .indexOf('.') + 2)));

            sensors.setLiquidTemperature(
            Double.parseDouble(sensors
                    .getLiquidTemperature()
                    .toString()
                    .substring(
                            0,
                            sensors
                                    .getLiquidTemperature()
                                    .toString()
                                    .indexOf('.') + 2)));

            dataDtos.add(sensorsMapper.map(sensors));
        });
        return dataDtos;
    }
}