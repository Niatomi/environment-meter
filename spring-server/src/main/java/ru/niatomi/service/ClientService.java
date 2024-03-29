package ru.niatomi.service;

import io.swagger.v3.oas.annotations.parameters.RequestBody;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Service;
import ru.niatomi.model.domain.arduinoConfig.ReferenceData;
import ru.niatomi.model.dto.configFiles.ReferenceDataDto;
import ru.niatomi.model.dto.data.DataDto;
import ru.niatomi.model.dto.time.ExactTimeDto;
import ru.niatomi.model.dto.time.TimePlanAndExactDto;
import ru.niatomi.model.dto.time.TimePlanDto;

import java.util.List;

/**
 * @author niatomi
 */
@Service
public interface ClientService {

    String updateReferenceData(ReferenceDataDto referenceData);

    String addExactTime(ExactTimeDto exactTimeDto);

    String addTimePlan(@RequestBody TimePlanDto timePlanDto);

    TimePlanAndExactDto getAllTime();

    List<DataDto> getData();


}
