#!/bin/sh

declare -a arr=("SentPackets" 
		"ReceivedUnicastPackets"
		"ReceivedBroadcasts"
		"SNIRLostPackets"
		"RXTXLostPackets"
		"TotalLostPackets"
		"DroppedPacketsInMac"
		"receivedFramesLowerMsg"
		"receivedBitsLowerPackets"
		"receivedBits"
		"packetsNotForMe"
		"chUtilizationSCH1"
		"chUtilizationSCH2"
		"chUtilizationSCH3"
		"chUtilizationSCH4"
		"chUtilizationCCH"
		)

declare -a sizes=("5") 

for metric in "${arr[@]}"
do
	echo "${metric}" 
	declare -a fileNamesWithMetric=($(grep -r "$metric" *.sca | awk -F '.sca:scalar' '{print $1}' | sort -u))
	echo "$fileNamesWithMetric"

	for fileName in "${fileNamesWithMetric[@]}"
	do
		fileNameWithMetric="${metric}"_"${fileName}".txt		
		echo "this is the file" "$fileNameWithMetric"
		grep -r "$metric" "${fileName}".sca > ../../../results_per_metric/"$fileNameWithMetric"
		#grep -r "$metric" SingleCH_Safety_B_100Bytes_Q_"$queueSize"-0.sca > ../../../results_per_metric/"$metric"_B_100_Q_"$queueSize".txt
		#grep -r "$metric" SingleCH_Safety_B_100Bytes_Q_"$queueSize"-0_27Mbitrate.sca > ../../../results_per_metric/"$metric"_B_100_Q_"$queueSize"_Bitrate_27.txt
	done
done

#ls ../../../results_per_metric/ 
