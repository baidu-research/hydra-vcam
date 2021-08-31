cp ../inference_lite_lib.armlinux.armv7hf/demo/cxx/ocr/debug/ocr_db_crnn ./  &
cp  ../mainApp/bin/mainApp ./ &
sudo ./mainApp &
./ocr_db_crnn &


