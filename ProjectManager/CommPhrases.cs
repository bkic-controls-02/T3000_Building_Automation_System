﻿
 */

#pragma warning disable 1591 // отключение warning CS1591: Missing XML comment for publicly visible type or member

namespace Scada.Comm
{
 
    public static class CommPhrases
    {
        static CommPhrases()
        {
            SetToDefault();
            InitOnLocalization();
        }

        // Словарь Scada.Comm.CommUtils
        public static string ParamRequired { get; private set; }
        public static string IncorrectParamVal { get; private set; }

        // Словарь Scada.Comm.Settings
        public static string LineCaption { get; private set; }
        public static string KPCaption { get; private set; }
        public static string IncorrectKPSettings { get; private set; }
        public static string IncorrectLineSettings { get; private set; }

        // Словарь Scada.Comm.Channels.FrmCommTcpClientProps
        public static string HostRequired { get; private set; }

        // Словарь Scada.Comm.Devices
        public static string SaveKpSettingsConfirm { get; private set; }
        public static string LoadKpDllSettingsError { get; private set; }
        public static string SaveKpDllSettingsError { get; private set; }
        public static string LoadKpSettingsError { get; private set; }
        public static string SaveKpSettingsError { get; private set; }
        public static string ConfigureKp { get; private set; }

        // Словарь Scada.Comm.Devices.KPFactory
        public static string GetViewTypeError { get; private set; }
        public static string CreateViewError { get; private set; }

        // Фразы, устанавливаемые в зависимости от локализации, не загружая из словаря
        public static string SendNotation { get; private set; }
        public static string ReceiveNotation { get; private set; }
        public static string ReadDataError { get; private set; }
        public static string ReadDataWithStopCondError { get; private set; }
        public static string ReadLinesError { get; private set; }
        public static string ReadAvailableError { get; private set; }
        public static string WriteDataError { get; private set; }
        public static string WriteLineError { get; private set; }
        public static string ClearDataStreamError { get; private set; }
        public static string NormalKpExecImpossible { get; private set; }
        public static string IllegalCommand { get; private set; }
        public static string IncorrectCmdData { get; private set; }
        public static string NoCmdData { get; private set; }
        public static string RetryDelay { get; private set; }
        public static string ResponseOK { get; private set; }
        public static string ResponseError { get; private set; }
        public static string ResponseCsError { get; private set; }
        public static string ResponseCrcError { get; private set; }
        public static string IncorrectResponseLength { get; private set; }
        public static string IncorrectResponseFormat { get; private set; }
        public static string On { get; private set; }
        public static string Off { get; private set; }


        private static void SetToDefault()
        {
            ParamRequired = "Требуется параметр \"{0}\".";
            IncorrectParamVal = "Некорректное значение параметра \"{0}\".";

            LineCaption = "Линия";
            KPCaption = "КП";
            IncorrectKPSettings = "Некорректные параметры КП {0}";
            IncorrectLineSettings = "Некорректная конфигурация линии связи {0}";

            HostRequired = "Требуется имя хоста.";

            SaveKpSettingsConfirm = "Настройки КП были изменены. Сохранить изменения?";
            LoadKpDllSettingsError = "Ошибка при загрузке настроек библиотеки КП";
            SaveKpDllSettingsError = "Ошибка при сохранении настроек библиотеки КП";
            LoadKpSettingsError = "Ошибка при загрузке настроек КП";
            SaveKpSettingsError = "Ошибка при сохранении настроек КП";
            ConfigureKp = "Создайте настройки КП и перезапустите службу Коммуникатора.";

            GetViewTypeError = "Ошибка при получении типа интерфейса КП из библиотеки {0}";
            CreateViewError = "Ошибка при создании экземпляра класса интерфейса КП {0}";
        }

        private static void InitOnLocalization()
        {
            if (Localization.UseRussian)
            {
                SendNotation = "Отправка";
                ReceiveNotation = "Приём";
                ReadDataError = "Ошибка при считывании данных";
                ReadDataWithStopCondError = "Ошибка при считывании данных с условием остановки";
                ReadLinesError = "Ошибка при считывании строк";
                ReadAvailableError = "Ошибка при считывании доступных данных";
                WriteDataError = "Ошибка при записи данных";
                WriteLineError = "Ошибка при записи строки";
                ClearDataStreamError = "Ошибка при очистке потока данных";
                NormalKpExecImpossible = "Нормальная работа КП невозможна";
                IllegalCommand = "Недопустимая команда";
                IncorrectCmdData = "Некорректные данные команды";
                NoCmdData = "Отсутствуют данные команды";
                RetryDelay = "Задержка перед повторной попыткой";
                ResponseOK = "OK!";
                ResponseError = "Ошибка связи!";
                ResponseCsError = "Ошибка КС!";
                ResponseCrcError = "Ошибка CRC!";
                IncorrectResponseLength = "Некорректная длина ответа!";
                IncorrectResponseFormat = "Некорректный формат ответа!";
                On = "Вкл";
                Off = "Откл";
            }
            else
            {
                SendNotation = "Send";
                ReceiveNotation = "Receive";
                ReadDataError = "Error reading data";
                ReadDataWithStopCondError = "Error reading data with stop condition";
                ReadLinesError = "Error reading lines";
                ReadAvailableError = "Error reading available data";
                WriteDataError = "Error writing data";
                WriteLineError = "Error writing line";
                ClearDataStreamError = "Error clearing data stream";
                NormalKpExecImpossible = "Normal device execution is impossible";
                IllegalCommand = "Illegal command";
                IncorrectCmdData = "Incorrect command data";
                NoCmdData = "No command data";
                RetryDelay = "Delay before trying again";
                ResponseOK = "OK!";
                ResponseError = "Communication error!";
                ResponseCsError = "CS error!";
                ResponseCrcError = "CRC error!";
                IncorrectResponseLength = "Incorrect response length!";
                IncorrectResponseFormat = "Incorrect response format!";
                On = "On";
                Off = "Off";
            }
        }

        public static void InitFromDictionaries()
        {
            Localization.Dict dict;
            if (Localization.Dictionaries.TryGetValue("Scada.Comm.CommUtils", out dict))
            {
                ParamRequired = dict.GetPhrase("ParamRequired", ParamRequired);
                IncorrectParamVal = dict.GetPhrase("IncorrectParamVal", IncorrectParamVal);
            }

            if (Localization.Dictionaries.TryGetValue("Scada.Comm.Settings", out dict))
            {
                LineCaption = dict.GetPhrase("LineCaption", LineCaption);
                KPCaption = dict.GetPhrase("KPCaption", KPCaption);
                IncorrectKPSettings = dict.GetPhrase("IncorrectKPSettings", IncorrectKPSettings);
                IncorrectLineSettings = dict.GetPhrase("IncorrectLineSettings", IncorrectLineSettings);
            }

            if (Localization.Dictionaries.TryGetValue("Scada.Comm.Channels.FrmCommTcpClientProps", out dict))
            {
                HostRequired = dict.GetPhrase("HostRequired", HostRequired);
            }

            if (Localization.Dictionaries.TryGetValue("Scada.Comm.Devices", out dict))
            {
                SaveKpSettingsConfirm = dict.GetPhrase("SaveKpSettingsConfirm", SaveKpSettingsConfirm);
                LoadKpDllSettingsError = dict.GetPhrase("LoadKpDllSettingsError", LoadKpDllSettingsError);
                SaveKpDllSettingsError = dict.GetPhrase("SaveKpDllSettingsError", SaveKpDllSettingsError);
                LoadKpSettingsError = dict.GetPhrase("LoadKpSettingsError", LoadKpSettingsError);
                SaveKpSettingsError = dict.GetPhrase("SaveKpSettingsError", SaveKpSettingsError);
                ConfigureKp = dict.GetPhrase("ConfigureKp", ConfigureKp);
            }

            if (Localization.Dictionaries.TryGetValue("Scada.Comm.Devices.KPFactory", out dict))
            {
                GetViewTypeError = dict.GetPhrase("GetViewTypeError", GetViewTypeError);
                CreateViewError = dict.GetPhrase("CreateViewError", CreateViewError);
            }
        }
    }
}
