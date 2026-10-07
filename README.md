# Aspida

Aspida is a privacy-friendly open source Android app which lets you track, analyze and block the connections made by the other apps in your device. It also allows you to export a PCAP dump of the traffic, inspect HTTP, decrypt TLS traffic and much more!

Aspida simulates a VPN in order to capture the network traffic without root. It does not use a remote VPN server, instead data is processed locally on the device.

Features:

- Log and examine the connections made by user and system apps
- Extract the SNI, DNS query, HTTP URL and the remote IP address
- Inspect HTTP requests and replies thanks to the built-in decoders
- Inspect the full connections payload as hexdump/text
- Decrypt the HTTPS/TLS traffic and export the SSLKEYLOGFILE
- Dump the traffic to a PCAP file, download it from a browser, or stream it to a remote receiver for real-time analysis (e.g. Wireshark)
- Create rules to filter out the good traffic and easily spot anomalies
- Identify the country and ASN of remote server via offline DB lookups
- On rooted devices, capture the traffic while other VPN apps are running

## Author

**Arunjith AS**

## Building

1. On Windows, install [gitforwindows](https://gitforwindows.org)
2. Clone this repo
3. Inside the repo dir, run `git submodule update --init`. The `submodules` directory should get populated.
4. Open the project in Android Studio, install the appropriate SDK and the NDK
5. Build the app

*Note*: If you get "No valid CMake executable was found", be sure to install the CMake version (currently 3.22.1) from the SDK manager.

## Open Source

Aspida is powered by open source technologies.

- [nDPI](https://github.com/ntop/nDPI): deep packet inspection library, provides the connections metadata
- [mitmproxy](https://github.com/mitmproxy/mitmproxy): a local proxy for the TLS decryption
- [zdtun](https://github.com/emanuele-f/zdtun): minimal TCP/IP stack for the non-root capture

Aspida is based on [PCAPdroid](https://github.com/emanuele-f/PCAPdroid) by Emanuele Faranda, licensed under GPLv3.

## License

This project is licensed under the GNU General Public License v3.0 — see the [LICENSE](LICENSE) file for details.
