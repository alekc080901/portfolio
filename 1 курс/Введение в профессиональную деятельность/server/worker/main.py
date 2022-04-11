import asyncio
import os
from subprocess import Popen, PIPE, TimeoutExpired

IP = os.environ.get("SOCK_HOST")
PORT = os.environ.get("SOCK_PORT")
FILE = os.environ.get("FILE_RUN_COMMAND")


def run_iteration(program_input):
    with Popen(FILE, stdin=PIPE, stdout=PIPE, stderr=PIPE) as process:
        try:
            program_output, error = process.communicate(program_input, timeout=10)  # Подставь нужное
        except TimeoutExpired:
            with open("error.txt", "w") as error_info:
                error_info.write("Превышено время выполнения программы")
            return

        if error is not None:
            with open("error.txt", "w") as error_info:
                error_info.write(error)
            return

    return program_output


async def run_program(loop):
    reader, writer = await asyncio.open_connection(IP, PORT, loop=loop)

    data = await reader.read()  # Сюда можно подставить количество байт для чтения. Если надо, подставь, пожалуйста

    output = run_iteration(data)

    if output is None:
        writer.write_eof()
        writer.close()
        await writer.wait_closed()
        return

    writer.write(output.encode())
    writer.close()


def main():
    loop = asyncio.get_event_loop()
    loop.run_until_complete(run_program(loop))
    loop.close()


if __name__ == "__main__":
    main()
