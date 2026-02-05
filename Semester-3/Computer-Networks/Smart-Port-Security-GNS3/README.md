# Smart Port Network Security Architecture
**Course:** Computer Communication & Networks Lab (Semester 3)
**Environment:** GNS3 (Integrated with VMware/VirtualBox)

##  Project Overview
This project replicates a **Real-World Smart Harbor** environment. It addresses the critical need for security in an integrated infrastructure where digital surveillance, cargo tracking, and administrative operations coexist. The architecture follows a **Multi-Zone Defense-in-Depth** strategy to prevent unauthorized access and perimeter vulnerabilities.

##  Security Architecture & Zones
The network is logically segmented into specific security zones to ensure granular control:
* **Administrative Zone (VLAN 10):** Secure network for management and harbor-master operations.
* **Operational Zone (VLAN 20):** Dedicated to port machinery, cargo tracking, and IoT sensors.
* **Surveillance Zone (VLAN 30):** High-bandwidth zone for real-time security camera feeds.
* **DMZ (Demilitarized Zone):** External-facing services isolated from the internal port network.



##  Technical Implementation
* **Defense-in-Depth:** Layered security using **FortiGate Firewalls** and Access Control Lists (ACLs).
* **GNS3 Virtualization:** Leveraged the GNS3 VM to run high-performance network nodes and Docker containers.
* **Inter-VLAN Routing:** Configured on the core "Harbor-Master" router to allow controlled communication between departments.
* **Traffic Validation:** Comprehensive testing including Perimeter Exit Validation and ICMP reachability audits.

##  Project Files
* **[port-report.pdf](./port-report.pdf):** Detailed 10+ page technical report covering topology, OSI mapping, and troubleshooting.
* **[Smart-Port-Project.gns3](./Smart-Port-Project.gns3):** The primary GNS3 project file containing the network topology and node configurations.

## 🛠️ Tech Stack
* **Simulation:** GNS3, VMware Workstation.
* **Security:** FortiGate Firewall, Cisco IOS.
* **Monitoring:** Wireshark (for packet inspection).
