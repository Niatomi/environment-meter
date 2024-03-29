package ru.niatomi.mapper;

import org.mapstruct.Mapper;
import org.mapstruct.Mapping;
import org.mapstruct.ReportingPolicy;
import ru.niatomi.model.domain.sensor.Sensors;
import ru.niatomi.model.dto.configFiles.SensorsDto;
import ru.niatomi.model.dto.data.DataDto;

import java.time.LocalDateTime;
import java.time.ZonedDateTime;

/**
 * @author niatomi
 */
@Mapper(
        componentModel = "spring",
        unmappedTargetPolicy = ReportingPolicy.IGNORE,
        imports = {
                LocalDateTime.class,
                ZonedDateTime.class
        }
)
public interface SensorsMapper {

    @Mapping(target = "timeOfCheck", expression = "java(LocalDateTime.now())")
    Sensors map(SensorsDto dto);

    DataDto map(Sensors sensors);

}
