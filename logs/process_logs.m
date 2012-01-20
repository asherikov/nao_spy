function process_logs(dir)
%
% dir - path to the directory containing logs.
%


try
    clear spy_joints
    load (strcat(dir, '/spy_joints.log'));

    if exist('spy_joints')
        Names = {
        ' 1 HEAD PITCH' \
        ' 2 HEAD YAW' \
        \
        ' 3 L ANKLE PITCH' \
        ' 4 L ANKLE ROLL' \
        ' 5 L ELBOW ROLL' \
        ' 6 L ELBOW YAW' \
        ' 7 L HIP PITCH' \
        ' 8 L HIP ROLL' \
        ' 9 L HIP YAW PITCH' \
        '10 L KNEE PITCH' \
        '11 L SHOULDER PITCH' \
        '12 L SHOULDER ROLL' \
        '13 L WRIST YAW' \
        \
        '14 R ANKLE PITCH' \
        '15 R ANKLE ROLL' \
        '16 R ELBOW ROLL' \
        '17 R ELBOW YAW' \
        '18 R HIP PITCH' \
        '19 R HIP ROLL' \
        '20 R KNEE PITCH' \
        '21 R SHOULDER PITCH' \
        '22 R SHOULDER ROLL' \
        '23 R WRIST YAW'};

        PlotSensors = {[3 14] [4 15] [7 18] [8 19] [10 20] [9]};

        Limits = [
        -2.085700,  2.085700;
        -0.672000,  0.514900;
        \
        -1.189516,  0.922747;
        -0.769001,  0.397880;
        -1.562100, -0.008700;
        -2.085600,  2.085600;
        -1.773912,  0.484090;
        -0.379472,  0.790477;
        -1.145303,  0.740810;
        -0.092346,  2.112528;
        -2.085600,  2.085600;
         0.008700,  1.649400;
        -1.823800,  1.823800;
        \
        -1.186448,  0.932056;
        -0.388676,  0.785875;
         0.008700,  1.562100;
        -2.085600,  2.085600;
        -1.772308,  0.485624;
        -0.738321,  0.414754;
        -0.103083,  2.120198;
        -2.085600,  2.085600;
        -1.649400, -0.008700;
        -1.823800,  1.823800;
        ];

        NumJoints = size(Names, 2);

        SensorValues = spy_joints(:,1:NumJoints);
        ActuatorValues = spy_joints(:,NumJoints+1:NumJoints*2);

        for i = 1:size(PlotSensors, 2);
            figure ('Position', get(0,'Screensize')*0.9);
            for j = 1:length(PlotSensors{i});
                subplot (length(PlotSensors{i}), 1, j);
                hold on;
                jointId = PlotSensors{i}(j);
                title (Names{1,jointId});
                plot (ActuatorValues(:,jointId), 'b');
                plot (SensorValues(:,jointId), 'r');
                axis ([0, size(SensorValues,1), Limits(jointId,1), Limits(jointId,2)]);
                legend ('ActuatorValues', 'SensorValues')
                hold off;
            end
        end

        % close all
    end
catch
end

try
    clear spy_com
    load (strcat(dir, '/spy_com.log'));

    if exist('spy_com')
        CoM_expected = spy_com(:, 1:3);
        CoM_sensor = spy_com(:, 4:6);
        CoM_igm = spy_com(:, 7:9);
        figure ('Position', get(0,'Screensize')*0.9);
        hold on;
        title ('CoM');
        plot3 (CoM_expected(:,1), CoM_expected(:,2), CoM_expected(:,3), 'b');
        plot3 (CoM_sensor(:,1), CoM_sensor(:,2), CoM_sensor(:,3), 'r');
        plot3 (CoM_igm(:,1), CoM_igm(:,2), CoM_igm(:,3), 'k');
        legend ('Expected', 'Computed from sensor data', 'Computed from sensor data using IGM')
        hold off;

        figure ('Position', get(0,'Screensize')*0.9);
        hold on;
        title ('Error in CoM position');
        plot(spy_com (:,1) - spy_com(:,4), 'b')
        plot(spy_com (:,2) - spy_com(:,5), 'r')
        plot(spy_com (:,3) - spy_com(:,6), 'k')
        legend ('along X axis', 'along Y axis', 'along Z axis');
        hold off;
    end
catch
end


try
    clear spy_left_foot
    clear spy_right_foot
    clear spy_swing_foot
    load (strcat(dir, '/spy_left_foot.log'));
    load (strcat(dir, '/spy_right_foot.log'));
    load (strcat(dir, '/spy_swing_foot.log'));

    if exist('spy_right_foot') && exist('spy_right_foot')
        sf_expected = spy_left_foot(:, 1:3);
        sf_sensor = spy_left_foot(:, 4:6);
        figure ('Position', get(0,'Screensize')*0.9);
        hold on;
        title ('foot position');
        plot3 (sf_expected(:,1), sf_expected(:,2), sf_expected(:,3), 'b');
        plot3 (sf_sensor(:,1), sf_sensor(:,2), sf_sensor(:,3), 'r');

        sf_expected = spy_right_foot(:, 1:3);
        sf_sensor = spy_right_foot(:, 4:6);
        plot3 (sf_expected(:,1), sf_expected(:,2), sf_expected(:,3), 'b');
        plot3 (sf_sensor(:,1), sf_sensor(:,2), sf_sensor(:,3), 'r');
        legend ('Expected', 'Computed from sensor data')

        sf_sensor = spy_swing_foot(:, 1:3);
        plot3 (sf_sensor(:,1), sf_sensor(:,2), sf_sensor(:,3), 'k');

        hold off;
    end
catch
end
